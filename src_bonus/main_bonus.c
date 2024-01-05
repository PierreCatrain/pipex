/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:23:31 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/04 22:25:34 by picatrai         ###   ########.fr       */
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
    if (ft_strncmp(line, argv[2], ft_strlen_gnl(argv[2])) == 1)
    {
        ft_putstr_fd(line, data->fd1);
        free(line);
        ft_complete(data, argv);
    }
    else
        free(line);
}

int    ft_here_doc_and_open(t_data_bonus *data, int argc, char **argv, int (*pipes)[2])
{
    if (ft_strncmp(argv[1], "here_doc", 8) == 0)
    {
        data->fd1 = open(".here_doc", O_CREAT | O_RDWR | O_TRUNC, 0777);
        if (data->fd1 < 0)
            return (ft_putstr_fd("error with infile\n", 2), -1);
        ft_complete(data, argv);
        close(data->fd1);
        data->fd1 = open(".here_doc", O_RDONLY);
        if (data->fd1 < 0)
        {
            unlink(".here_doc");
            return (ft_putstr_fd("error with infile\n", 2), -1);
        }
        unlink(".here_doc");
        data->fd2 = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0777);
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
    // char buffer[10];//
    // int size;//

    data.args_cmd = ft_split(argv[data.index_cmd + 2], ' ');
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
    // size = read(fd_in, &buffer, 10);
    // ft_putnbr_fd(size, 2);
    // ft_putstr_fd("d\n", 2);
    // buffer[size] = '\0';
    // ft_putstr_fd("g\n", 2);
    // ft_putstr_fd(buffer, 2);
    // free(buffer);
    ft_putnbr_fd(fd_in, 2);
    ft_putnbr_fd(fd_out, 2);
    close(fd_in);
    close(fd_out);
    ft_putstr_fd("e\n", 2);
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
            //waitpid(-1, NULL, 0);
        }
        data.index_cmd++;
    }
    // waitpid(data.pid, NULL, 0);
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
    {
        data.index_cmd = 0;
        data.nb_pipe = argc - 4;
    }
    else
    {
        data.index_cmd = 1;
        data.nb_pipe = argc - 4;
    }
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