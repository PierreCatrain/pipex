/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:28:38 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/09 22:46:57 by picatrai         ###   ########.fr       */
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
    char    *str_here;
    char    *str_index;
    int     here_res;
    char    **args_cmd;
    char    *path_cmd;
    int     index_cmd;
}   t_data_bonus;

void    free_2d(char **str);
void    ft_close(t_data data, int n);
void    ft_close_bonus(t_data_bonus data, int (*pipes)[2], int n);
void    ft_putstr_fd(char *str, int fd);
void    close_fail_pipe(int (*pipes)[2], int index);

char	**ft_split(char *str, char c);
char *ft_get_path_cmd(char *command, char **envp);
int	ft_strncmp(char *s1, char *s2, int n);


void    ft_close_pipe_useless(t_data_bonus data, int (*pipes)[2], int *fd_in, int *fd_out);
int    ft_here_doc_and_open(t_data_bonus *data, int argc, char **argv, int (*pipes)[2]);

# define BUFFER_SIZE 10

size_t	ft_strlen_gnl(char *str);
int	ft_check_line(char *stockage);
char	*ft_clean(char *stockage, int i, int j);
char	*ft_cut(char *stockage);
char	*get_next_line(int fd);

int     ft_strlen(char *str);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_itoa(int n);

#endif