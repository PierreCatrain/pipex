/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:23:31 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/09 23:31:23 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	ft_child_bonus(t_data_bonus data, char **argv, \
		char **envp, int (*pipes)[2])
{
	int	fd_in;
	int	fd_out;
	int	ecart;

	ecart = 2;
	if (data.here_res == 1)
		ecart++;
	data.args_cmd = ft_split(argv[data.index_cmd + ecart], ' ');
	if (data.args_cmd == NULL)
		exit(EXIT_FAILURE);
	data.path_cmd = ft_get_path_cmd(data.args_cmd[0], envp);
	if (data.path_cmd == NULL)
	{
		free_2d(data.args_cmd);
		ft_putstr_fd("error with command\n", 2);
		exit(EXIT_FAILURE);
	}
	ft_close_pipe_useless(data, pipes, &fd_in, &fd_out);
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_in);
	close(fd_out);
	execve(data.path_cmd, data.args_cmd, envp);
	free_2d(data.args_cmd);
	free(data.path_cmd);
	ft_putstr_fd("error with execve\n", 2);
	exit(EXIT_FAILURE);
}

void	suite(t_data_bonus data, char **argv, char **envp, int (*pipes)[2])
{
	while (data.index_cmd < data.nb_pipe)
	{
		data.pid = fork();
		if (data.pid == -1)
		{
			ft_close_bonus(data, pipes, 4);
			exit(EXIT_FAILURE);
		}
		else if (data.pid == 0)
		{
			ft_child_bonus(data, argv, envp, pipes);
			wait(NULL);
		}
		data.index_cmd++;
	}
	ft_child_bonus(data, argv, envp, pipes);
}

int	main(int argc, char **argv, char **envp)
{
	t_data_bonus	data;
	int			i;
	int			pipes[argc - 4][2];
	
	data.argc = argc;
	if (argc < 4)
		return (ft_putstr_fd("error with arguments\n", 2), 0);
	data.here_res = ft_here_doc_and_open(&data, argc, argv, pipes);
	if (data.here_res == -1)
		return (0);
	else if (data.here_res == 0)
		data.nb_pipe = argc - 4;
	else
		data.nb_pipe = argc - 5;
	data.index_cmd = 0;
	i = 0;
	while (i < data.nb_pipe)
	{
		if (pipe(pipes[i]) == -1)
			return (close_fail_pipe(pipes, i), \
					ft_close_bonus(data, pipes, 3), 0);
		i++;
	}
	suite(data, argv, envp, pipes);
	return (0);
}
