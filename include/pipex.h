/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:28:38 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/02 19:12:32 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_data
{
    int     fd_pipe[2];
    int     pid;
    int     fd1;
    int     fd2;
    char    **args_cmd1;
    char    **args_cmd2;
    char    *path_cmd1;
    char    *path_cmd2;
}   t_data;

typedef struct s_data_bonus
{
    int     argc;
    int     nb_pipe;
    int     pid;
    int     fd1;
    int     fd2;
    char    **args_cmd;
    char    *path_cmd;
    int     index_cmd;
}   t_data_bonus;

void    free_2d(char **str);
void    close_all(t_data *data);
void    ft_putstr_fd(char *str, int fd);
void    close_fail_pipe(int (*pipes)[2], int index);

char	**ft_split(char *str, char c);
char *ft_get_path_cmd(char *command, char **envp);


void    ft_close_pipe_useless(t_data_bonus data, int (*pipes)[2], int *fd_in, int *fd_out);

#endif