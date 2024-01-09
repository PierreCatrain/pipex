/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:36:20 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/09 23:03:27 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	ft_child(t_data data, char **argv, char **envp)
{
	data.args_cmd1 = ft_split(argv[2], ' ');
	if (data.args_cmd1 == NULL)
		exit(EXIT_FAILURE);
	data.path_cmd1 = ft_get_path_cmd(data.args_cmd1[0], envp);
	if (data.path_cmd1 == NULL)
	{
		free_2d(data.args_cmd1);
		ft_putstr_fd("error with command 1\n", 2);
		exit(EXIT_FAILURE);
	}
	dup2(data.fd1, STDIN_FILENO);
	dup2(data.fd_pipe[1], STDOUT_FILENO);
	ft_close(data, 4);
	execve(data.path_cmd1, data.args_cmd1, envp);
	free_2d(data.args_cmd1);
	free(data.path_cmd1);
	ft_putstr_fd("error with execve 1\n", 2);
	exit(EXIT_FAILURE);
}

void	ft_parent(t_data data, char **argv, char **envp)
{
	data.args_cmd2 = ft_split(argv[3], ' ');
	if (data.args_cmd2 == NULL)
		exit(EXIT_FAILURE);
	data.path_cmd2 = ft_get_path_cmd(data.args_cmd2[0], envp);
	if (data.path_cmd2 == NULL)
	{
		free_2d(data.args_cmd2);
		ft_putstr_fd("error with command 2\n", 2);
		exit(EXIT_FAILURE);
	}
	dup2(data.fd_pipe[0], STDIN_FILENO);
	dup2(data.fd2, STDOUT_FILENO);
	ft_close(data, 4);
	execve(data.path_cmd2, data.args_cmd2, envp);
	free_2d(data.args_cmd2);
	free(data.path_cmd2);
	ft_putstr_fd("error with execve 2\n", 2);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc != 5)
		return (ft_putstr_fd("error with arguments\n", 2), 0);
	data.fd1 = open(argv[1], O_RDONLY);
	if (data.fd1 < 0)
		return (ft_putstr_fd("error with infile\n", 2), 0);
	data.fd2 = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (data.fd2 < 0)
		return (ft_putstr_fd("error with outfile\n", 2), ft_close(data, 1), 0);
	if (pipe(data.fd_pipe) == -1)
		return (ft_close(data, 3), 0);
	data.pid = fork();
	if (data.pid == -1)
		return (ft_putstr_fd("fork fail\n", 2), ft_close(data, 3), 0);
	else if (data.pid == 0)
		ft_child(data, argv, envp);
	waitpid(data.pid, NULL, 0);
	ft_parent(data, argv, envp);
}
