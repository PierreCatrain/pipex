/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_close_error_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 17:53:59 by picatrai          #+#    #+#             */
/*   Updated: 2023/12/18 18:52:42 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void    free_args_bonus(t_data_bonus data)
{
    int i;
    
    i = 0;
    while (data.args_cmd[i])
        free(data.args_cmd[i++]);
    free(data.args_cmd);
}

void    close_all_bonus(t_data_bonus *data, int (*pipes)[2])
{
    int i;

    i = -1;
    while (++i < data->nb_pipe)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }
    close(data->fd1);
    close(data->fd2);
    // close(data->fd3);
}

void    ft_close_pipe_start(t_data_bonus data, int (*pipes)[2])
{
    int i;

    if (data.nb_pipe == 0)
    {
        i = -1;
        while (++i < data.nb_pipe)
        {
            close(pipes[i][0]);
            close(pipes[i][1]);
        }
    }
    else if (data.index_cmd == 0)
    {
        i = -1;
        while (++i < data.nb_pipe)
        {
            close(pipes[i][0]);
            if (data.index_cmd != i)
                close(pipes[i][1]);
        }
        close(data.fd2);
    }
    else if (data.index_cmd == data.argc - 4)
    {
        i = -1;
        while (++i < data.nb_pipe)
        {
            if (data.index_cmd - 1 != i)
                close(pipes[i][0]);
            close(pipes[i][1]);
        }
        close(data.fd1);
    }   
    else
    {
        i = -1;
        while (++i < data.nb_pipe)
        {
            if (data.index_cmd - 1 != i)
                close(pipes[i][0]);
            if (data.index_cmd != i)
                close(pipes[i][1]);
        }
        close(data.fd1);
        close(data.fd2);
    }
}

void    free_path_env(char **path_env)
{
    int i;

    i= 0;
    while (path_env[i])
        free(path_env[i++]);
    free(path_env);
}

void    ft_putstr_fd(char *str, int fd)
{
    int i;
    
    i = 0;
    while (str[i])
        write(fd, &str[i++], 1);
}