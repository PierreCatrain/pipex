/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:23:31 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/02 19:22:08 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void    ft_child_bonus(t_data_bonus data, char **argv, char **envp, int (*pipes)[2])
{
    int fd_in;
    int fd_out;
    
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
    data.index_cmd = 0;
    while (data.index_cmd < data.argc - 4)
    {
        data.pid = fork();
        if (data.pid == -1)
            exit(EXIT_FAILURE);
        else if (data.pid == 0)
        {
            ft_child_bonus(data, argv, envp, pipes);
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

    if (argc < 4)
        return (ft_putstr_fd("error with arguments\n", 2), 0);
    data.fd1 = open(argv[1], O_RDONLY);
    if (data.fd1 < 0)
        return (ft_putstr_fd("error with infile\n", 2), 0);
    data.fd2 = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0777);
    if (data.fd2 < 0)
        return (ft_putstr_fd("error with outfile\n", 2), 0);
    data.nb_pipe = argc - 4;
    data.argc = argc;
    i = 0;
    while (i < data.nb_pipe)
    {
        if (pipe(pipes[i]) == -1)
            return (close_fail_pipe(pipes, i), 0);
        i++;
    }
    suite(data, argv, envp, pipes);
    return (0);
}
