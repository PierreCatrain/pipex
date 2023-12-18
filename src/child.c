/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:51:16 by picatrai          #+#    #+#             */
/*   Updated: 2023/12/12 19:33:41 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void    ft_child_1(t_data data, char **argv, char **envp)
{   
    data.args_cmd1 = ft_split(argv[2], ' ');
    if (data.args_cmd1 == NULL)
        exit(EXIT_FAILURE);
    data.path_cmd1 = ft_get_path_cmd(data.args_cmd1[0], envp);
    if (data.path_cmd1 == NULL)
    {
        free_args_1(data);
        perror("error with command 1");
        exit(EXIT_FAILURE);
    }
    dup2(data.fd1, STDIN_FILENO);
    dup2(data.fd_pipe[1], STDOUT_FILENO);
    close_all(&data);
    execve(data.path_cmd1, data.args_cmd1, envp);
    free_args_1(data);
    free(data.path_cmd1);
    perror("error with execve 1");
    exit(EXIT_FAILURE);
}

void    ft_child_2(t_data data, char **argv, char **envp)
{
    data.args_cmd2 = ft_split(argv[3], ' ');
    if (data.args_cmd2 == NULL)
        exit(EXIT_FAILURE);
    data.path_cmd2 = ft_get_path_cmd(data.args_cmd2[0], envp);
    if (data.path_cmd2 == NULL)
    {
        free_args_2(data);
        perror("error with command 2");
        exit(EXIT_FAILURE);
    }
    dup2(data.fd_pipe[0], STDIN_FILENO);
    dup2(data.fd2, STDOUT_FILENO);
    close_all(&data);
    execve(data.path_cmd2, data.args_cmd2, envp);
    free_args_2(data);
    free(data.path_cmd2);
    perror("error with execve 2");
    exit(EXIT_FAILURE);
}