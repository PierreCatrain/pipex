/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:36:20 by picatrai          #+#    #+#             */
/*   Updated: 2023/12/12 19:33:47 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int     main(int argc, char **argv, char **envp)
{
    t_data data;

    if (argc != 5)
        return (ft_putstr_fd("error with arguments\n", 2), 0);
    data.fd1 = open(argv[1], O_RDONLY);
    if (data.fd1 < 0)
        return (perror("error with infile"), 0);
    data.fd2 = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0777);
    if (data.fd2 < 0)
        return (perror("error with outfile"), 0);
    if (pipe(data.fd_pipe) == -1)
        return (0);
    data.pid1 = fork();
    if (data.pid1 == -1)
        return (0);
    else if (data.pid1 == 0)
        ft_child_1(data, argv, envp);
    data.pid2 = fork();
    if (data.pid2 == -1)
        return (0);
    else if (data.pid2 == 0)
        ft_child_2(data, argv, envp);
    close_all(&data);
    waitpid(data.pid1, NULL, 0);
    waitpid(data.pid2, NULL, 0);
}