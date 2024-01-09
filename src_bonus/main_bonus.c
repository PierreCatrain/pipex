/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:23:31 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/09 21:31:04 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else if (n < 0)
	{
		ft_putchar_fd(('-'), fd);
		ft_putnbr_fd(-n, fd);
	}
	else if (n > 9)
	{
		ft_putnbr_fd((n / 10), fd);
		ft_putnbr_fd((n % 10), fd);
	}
	else
		ft_putchar_fd((n + '0'), fd);
}


void     ft_complete(t_data_bonus *data, char **argv)
{
    char *line;

    ft_putstr_fd("here_doc> ", 1);
    line = get_next_line(0);
    if (ft_strncmp(line, argv[2], ft_strlen_gnl(argv[2])) == 1 || ft_strlen(argv[2]) != ft_strlen(line) - 1)
    {
        ft_putstr_fd(line, data->fd1);
        free(line);
        ft_complete(data, argv);
    }
    else
        free(line);
}

static int	ft_count(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		count++;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*itoa;
	int		len;
	long	long_n;

	len = ft_count(n);
	long_n = n;
	itoa = (char *)malloc((len + 1) * sizeof(char));
	if (itoa == NULL)
		return (NULL);
	itoa[len] = '\0';
	if (long_n < 0)
		long_n *= -1;
	while (len > 0)
	{
		itoa[len - 1] = (long_n % 10) + '0';
		long_n /= 10;
		len--;
	}
	if (n < 0)
	itoa[0] = '-';
	return (itoa);
}

int     ft_get_str_here(char *str, t_data_bonus *data)
{
    int index;

    index = 1;
    while (index <= 999)
    {
        data->str_index = ft_itoa(index);
        if (data->str_index == NULL)
            return (0);
        data->str_here = ft_strjoin(str, data->str_index);
        if (data->str_here == NULL)
            return (free(data->str_index), 0);
        if (access(data->str_here, 0) != 0)
            return (1);
        else
        {
            free(data->str_here);
            free(data->str_index);
        }
        index++;
    }
    return (0);
}

int    ft_here_doc_and_open(t_data_bonus *data, int argc, char **argv, int (*pipes)[2])
{
    if (ft_strncmp(argv[1], "here_doc", 8) == 0 && ft_strlen(argv[1]) == 8)
    {
        if (ft_get_str_here(".here_doc", data) == 0)
            return (-1);
        data->fd1 = open(".here_doc", O_CREAT | O_RDWR | O_TRUNC, 0777);
        if (data->fd1 < 0)
            return (ft_putstr_fd("error with infile\n", 2), free(data->str_here), free(data->str_index), -1);
        ft_complete(data, argv);
        close(data->fd1);
        data->fd1 = open(".here_doc", O_RDWR, 0777);
        if (data->fd1 < 0)
        {
            unlink(".here_doc");
            free(data->str_here);
            free(data->str_index);
            return (ft_putstr_fd("error with infile\n", 2), -1);
        }
        unlink(".here_doc");
        free(data->str_here);
        free(data->str_index);
        data->fd2 = open(argv[argc - 1], O_CREAT | O_WRONLY | O_APPEND, 0777);
        if (data->fd2 < 0)
            return (ft_putstr_fd("error with outfile\n", 2), ft_close_bonus(*data, pipes, 1), -1);
        return (1);
    }
    else
    {
        data->fd1 = open(argv[1], O_RDONLY);
        if (data->fd1 < 0)
            return (ft_putstr_fd("error with infile\n", 2), -1);
        data->fd2 = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0777);
        if (data->fd2 < 0)
            return (ft_putstr_fd("error with outfile\n", 2), ft_close_bonus(*data, pipes, 1), -1);
    }
    return (0);
}

void    ft_child_bonus(t_data_bonus data, char **argv, char **envp, int (*pipes)[2])
{
    int fd_in;
    int fd_out;
    int ecart;

    ecart = 2;
    if (data.here_res == 1)
        ecart++;
    data.args_cmd = ft_split(argv[data.index_cmd + ecart], ' ');
    if (data.args_cmd == NULL)
        exit(EXIT_FAILURE);
    data.path_cmd = ft_get_path_cmd(data.args_cmd[0], envp);
    if (data.path_cmd == NULL)
    {
        free_2d(data.args_cmd);
        ft_putstr_fd("error with command\n", 2);
        exit(EXIT_FAILURE);
    }
    ft_close_pipe_useless(data, pipes, &fd_in, &fd_out);
    dup2(fd_in, STDIN_FILENO);
    dup2(fd_out, STDOUT_FILENO);
    close(fd_in);
    close(fd_out);
    execve(data.path_cmd, data.args_cmd, envp);
    free_2d(data.args_cmd);
    free(data.path_cmd);
    ft_putstr_fd("error with execve\n", 2);
    exit(EXIT_FAILURE);
}

void    suite(t_data_bonus data, char **argv, char **envp, int (*pipes)[2])
{
    while (data.index_cmd < data.nb_pipe)
    {
        data.pid = fork();
        if (data.pid == -1)
        {
            ft_close_bonus(data, pipes, 3);
            exit(EXIT_FAILURE);
        }
        else if (data.pid == 0)
        {
            ft_child_bonus(data, argv, envp, pipes);
            wait(NULL);
        }
        data.index_cmd++;
    }
    ft_child_bonus(data, argv, envp, pipes);
}

int     main(int argc, char **argv, char **envp)
{
    t_data_bonus data;
    int i;
    int pipes[argc - 4][2];

    data.argc = argc;
    if (argc < 4)
        return (ft_putstr_fd("error with arguments\n", 2), 0);
    data.here_res = ft_here_doc_and_open(&data, argc, argv, pipes);
    if (data.here_res == -1)
        return (0);
    else if (data.here_res == 0)
        data.nb_pipe = argc - 4;
    else
        data.nb_pipe = argc - 5;
    data.index_cmd = 0;
    i = 0;
    while (i < data.nb_pipe)
    {
        if (pipe(pipes[i]) == -1)
            return (close_fail_pipe(pipes, i), 0); // close fd1 et fd2
        i++;
    }
    suite(data, argv, envp, pipes);
    return (0);
}

/*
les wait
les heredocs
tout bien close
norme
*/