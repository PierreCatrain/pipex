/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_close_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:47:33 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/02 19:15:10 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void    free_2d(char **str)
{
    int i;
    
    i = 0;
    while (str[i])
        free(str[i++]);
    free(str);
}

void    close_all(t_data *data)
{
    close(data->fd_pipe[0]);
    close(data->fd_pipe[1]);
    close(data->fd1);
    close(data->fd2);
}

void    close_fail_pipe(int (*pipes)[2], int index)
{
    while (index >= 0)
    {
        close(pipes[index][0]);
        close(pipes[index][1]);
        index--;
    }
}

void    ft_putstr_fd(char *str, int fd)
{
    int i;

    i = 0;
    while (str[i])
        write(fd, &str[i++], 1);
}