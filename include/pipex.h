/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:28:38 by picatrai          #+#    #+#             */
/*   Updated: 2023/12/18 18:55:40 by picatrai         ###   ########.fr       */
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
    int     pid1;
    int     pid2;
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
    int     fd3;//
    char    **args_cmd;
    char    *path_cmd;
    int     index_cmd;
}   t_data_bonus;

void    free_args_1(t_data data);
void    free_args_2(t_data data);
void    free_path_env(char **path_env);
void    close_all(t_data *data);
void    ft_putstr_fd(char *str, int fd);

char	**ft_split(char *str, char c);

char *ft_get_path_cmd(char *command, char **envp);

void    ft_child_1(t_data data, char **argv, char **envp);
void    ft_child_2(t_data data, char **argv, char **envp);









void    free_args_bonus(t_data_bonus data);
void    close_all_bonus(t_data_bonus *data, int (*pipes)[2]);

void    ft_close_pipe_start(t_data_bonus data, int (*pipes)[2]);
void	ft_putnbr_fd(int n, int fd);
void	ft_putchar_fd(char c, int fd);

#endif