/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_close_error_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 17:53:59 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/02 18:54:11 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void    ft_utils_one_command(t_data_bonus data, int (*pipes)[2], int *fd_in, int *fd_out)
{
    int i;

    i = -1;
    while (++i < data.nb_pipe)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }
    *fd_in = data.fd1;
    *fd_out = data.fd2;
}

void    ft_utils_first_command(t_data_bonus data, int (*pipes)[2], int *fd_in, int *fd_out)
{
    int i;

    i = -1;
    while (++i < data.nb_pipe)
    {
        close(pipes[i][0]);
        if (data.index_cmd != i)
            close(pipes[i][1]);
    }
    close(data.fd2);
    *fd_in = data.fd1;
    *fd_out = pipes[0][1];
}

void    ft_utils_last_command(t_data_bonus data, int (*pipes)[2], int *fd_in, int *fd_out)
{
    int i;

    i = -1;
    while (++i < data.nb_pipe)
    {
        if (data.index_cmd - 1 != i)
            close(pipes[i][0]);
        close(pipes[i][1]);
    }
    close(data.fd1);
    *fd_in = pipes[data.argc - 5][0];
    *fd_out = data.fd2;
}

void    ft_utils(t_data_bonus data, int (*pipes)[2], int *fd_in, int *fd_out)
{
    int i;

    i = -1;
    while (++i < data.nb_pipe)
    {
        if (data.index_cmd - 1 != i)
            close(pipes[i][0]);
        else
            *fd_in = pipes[i][0];
        if (data.index_cmd != i)
            close(pipes[i][1]);
        else
            *fd_out = pipes[i][1];
    }
    close(data.fd1);
    close(data.fd2);
}

void    ft_close_pipe_useless(t_data_bonus data, int (*pipes)[2], int *fd_in, int *fd_out)
{
    if (data.nb_pipe == 0)
        ft_utils_one_command(data, pipes, fd_in, fd_out);
    else if (data.index_cmd == 0)
        ft_utils_first_command(data, pipes, fd_in, fd_out);
    else if (data.index_cmd == data.argc - 4)
        ft_utils_last_command(data, pipes, fd_in, fd_out);
    else
        ft_utils(data, pipes, fd_in, fd_out);
}