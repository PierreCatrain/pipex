/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_close_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:47:33 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/04 18:06:01 by picatrai         ###   ########.fr       */
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

void    close_fail_pipe(int (*pipes)[2], int index)
{
    while (index >= 0)
    {
        close(pipes[index][0]);
        close(pipes[index][1]);
        index--;
    }
}

void    ft_close(t_data data, int n)
{
    if (n == 1)
        close(data.fd1);
    else if (n == 2)
        close(data.fd2);
    else if (n == 3)
    {
        close(data.fd1);
        close(data.fd2);
    }
    else if (n == 4)
    {
        close(data.fd1);
        close(data.fd2);
        close(data.fd_pipe[0]);
        close(data.fd_pipe[1]);
    }
}   

void    ft_close_bonus(t_data_bonus data, int (*pipes)[2], int n)
{
    int    i;

    i = -1;
    if (n == 0)
    {
        while (++i < data.nb_pipe)
        {
            close(pipes[i][0]);
            close(pipes[i][1]);
        }
    }
    else if (n == 1)
    {
        close(data.fd1);
        ft_close_bonus(data, pipes, 0);
    }
    else if (n == 2)
    {
        close(data.fd2);
        ft_close_bonus(data, pipes, 0);
    }
    else if (n == 3)
    {
        close(data.fd1);
        close(data.fd2);
        ft_close_bonus(data, pipes, 0);
    }
}

void    ft_putstr_fd(char *str, int fd)
{
    int i;

    i = 0;
    while (str[i])
        write(fd, &str[i++], 1);
}