/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:23:31 by picatrai          #+#    #+#             */
/*   Updated: 2023/12/18 17:48:00 by picatrai         ###   ########.fr       */
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

void    ft_child_bonus(t_data_bonus data, char ** argv, char **envp, int (*pipes)[2])
{
    ft_putstr_fd("\n", data.fd3);//
    ft_putstr_fd(argv[data.index_cmd + 2], data.fd3);//
    ft_putstr_fd("\n", data.fd3);//
    data.args_cmd = ft_split(argv[data.index_cmd + 2], ' ');
    if (data.args_cmd == NULL)
        exit(EXIT_FAILURE);
    data.path_cmd = ft_get_path_cmd(data.args_cmd[0], envp);
    if (data.path_cmd == NULL)
    {
        free_args_bonus(data);
        perror("error with command");
        exit(EXIT_FAILURE);
    }
    if (data.nb_pipe == 0)
    {
        ft_putstr_fd("in file1\n", data.fd3);//
        ft_putstr_fd("out file2\n", data.fd3);//
        dup2(data.fd1, STDIN_FILENO);
        dup2(data.fd2, STDOUT_FILENO);
    }
    else if (data.index_cmd == 0)
    {
        ft_putstr_fd("in file1\n", data.fd3);//
        ft_putstr_fd("out 0 1\n", data.fd3);//
        dup2(data.fd1, STDIN_FILENO);
        dup2(pipes[0][1], STDOUT_FILENO);
    }
    else if (data.index_cmd == data.argc - 4)
    {
        ft_putstr_fd("in ", data.fd3);//
        ft_putnbr_fd(data.index_cmd - 1, data.fd3);//
        ft_putstr_fd(" 0\n", data.fd3);//
        ft_putstr_fd("out file2\n", data.fd3);//
        dup2(pipes[data.index_cmd - 1][0], STDIN_FILENO);
        dup2(data.fd2, STDOUT_FILENO);
    }   
    else
    {
        ft_putstr_fd("in ", data.fd3);//
        ft_putnbr_fd(data.index_cmd - 1, data.fd3);//
        ft_putstr_fd(" 0\n", data.fd3);//
        ft_putstr_fd("out ", data.fd3);//
        ft_putnbr_fd(data.index_cmd, data.fd3);//
        ft_putstr_fd(" 1\n", data.fd3);//
        dup2(pipes[data.index_cmd - 1][0], STDIN_FILENO);
        dup2(pipes[data.index_cmd][1], STDOUT_FILENO);
    }
    close_all_bonus(&data, pipes);
    execve(data.path_cmd, data.args_cmd, envp);
    free_args_bonus(data);
    free(data.path_cmd);
    perror("error with execve");
    exit(EXIT_FAILURE);
}

int     main(int argc, char **argv, char **envp)
{
    t_data_bonus data;

    if (argc < 4)
        return (ft_putstr_fd("error with arguments\n", 2), 0);
    data.fd1 = open(argv[1], O_RDONLY);
    if (data.fd1 < 0)
        return (perror("error with infile"), 0);
    data.fd2 = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0777);
    if (data.fd2 < 0)
        return (perror("error with outfile"), 0);
    data.nb_pipe = argc - 4;
    data.argc = argc;

    data.fd3 = open("file3", O_RDWR);//
    int i;
    int pipes[data.nb_pipe][2];
    
    i = 0;
    while (i < data.nb_pipe)
    {
        if (pipe(pipes[i]) == -1)
            return (0); // va falloir close celle deja ouverte
        i++;
    }

    data.index_cmd = 0;
    while (data.index_cmd < argc - 3)
    {
        data.pid = fork();
        if (data.pid == -1)
            return (0);
        else if (data.pid == 0)
            ft_child_bonus(data, argv, envp, pipes);
        waitpid(data.pid, NULL, 0);
        data.index_cmd++;
    }
    close(data.fd3);
    close_all_bonus(&data, pipes);
}

/*

file1
cat 2
pipe 0 1

pipe 0 0
cat 3
pipe 1 1

pipe 1 0
cat 4
pipe 2 1

pipe 2 0
cat 5
pipe 3 1

pipe 3 0
cat 6
file2


nb - 2

*/