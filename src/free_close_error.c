/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_close_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:47:33 by picatrai          #+#    #+#             */
/*   Updated: 2023/12/12 19:32:56 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void    free_args_1(t_data data)
{
    int i;
    
    i = 0;
    while (data.args_cmd1[i])
        free(data.args_cmd1[i++]);
}

void    free_args_2(t_data data)
{
    int i;
    
    i = 0;
    while (data.args_cmd2[i])
        free(data.args_cmd2[i++]);
}

void    free_path_env(char **path_env)
{
    int i;

    i= 0;
    while (path_env[i])
        free(path_env[i++]);
    free(path_env);
}

void    close_all(t_data *data)
{
    close(data->fd_pipe[0]);
    close(data->fd_pipe[1]);
    close(data->fd1);
    close(data->fd2);
}

void    ft_putstr_fd(char *str, int fd)
{
    int i;
    
    i = 0;
    while (str[i])
        write(fd, &str[i++], 1);
}