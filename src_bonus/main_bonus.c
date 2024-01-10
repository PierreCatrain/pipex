/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:23:31 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/10 02:11:31 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	ft_get_arg_exec(t_data_bonus *data, char **argv, \
		char **envp, int **pipes)
{
	int	ecart;

	ecart = 2;
	if (data->here_res == 1)
		ecart++;
	data->args_cmd = ft_split(argv[data->index_cmd + ecart], ' ');
	if (data->args_cmd == NULL)
	{
		free_pipes(pipes, data->nb_pipe);
		exit(EXIT_FAILURE);
	}
	data->path_cmd = ft_get_path_cmd(data->args_cmd[0], envp);
	if (data->path_cmd == NULL)
	{
		free_2d(data->args_cmd);
		free_pipes(pipes, data->nb_pipe);
		ft_putstr_fd("error with command\n", 2);
		exit(EXIT_FAILURE);
	}
}

void	ft_child_bonus(t_data_bonus data, char **argv, \
		char **envp, int **pipes)
{
	int	fd_in;
	int	fd_out;

	ft_get_arg_exec(&data, argv, envp, pipes);
	ft_close_pipe_useless(data, pipes, &fd_in, &fd_out);
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_in);
	close(fd_out);
	free_pipes(pipes, data.nb_pipe);
	execve(data.path_cmd, data.args_cmd, envp);
	free_2d(data.args_cmd);
	free(data.path_cmd);
	free_pipes(pipes, data.nb_pipe);
	ft_putstr_fd("error with execve\n", 2);
	exit(EXIT_FAILURE);
}

void	suite(t_data_bonus data, char **argv, char **envp, int **pipes)
{
	while (data.index_cmd < data.nb_pipe)
	{
		data.pid = fork();
		if (data.pid == -1)
		{
			ft_close_bonus(data, pipes, 4);
			free_pipes(pipes, data.nb_pipe);
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

int	**init_pipes(t_data_bonus data)
{
	int			i;
	int			**pipes;

	pipes = (int **)malloc(data.nb_pipe * sizeof(int *));
	if (pipes == NULL)
	{
		ft_putstr_fd("Erreur d'allocation de mémoire pour les pipes", 2);
		exit(EXIT_FAILURE);
	}
	i = -1;
	while (++i < data.nb_pipe)
	{
		pipes[i] = (int *)malloc(2 * sizeof(int));
		if (pipes[i] == NULL)
			init_error_1(data, pipes, i);
		if (pipe(pipes[i]) == -1)
			init_error_2(data, pipes, i);
	}
	return (pipes);
}

int	main(int argc, char **argv, char **envp)
{
	t_data_bonus	data;
	int				**pipes;

	data.argc = argc;
	if (argc < 4)
		return (ft_putstr_fd("error with arguments\n", 2), 0);
	data.here_res = ft_here_doc_and_open(&data, argc, argv);
	if (data.here_res == -1)
		return (0);
	else if (data.here_res == 0)
		data.nb_pipe = argc - 4;
	else
		data.nb_pipe = argc - 5;
	data.index_cmd = 0;
	pipes = init_pipes(data);
	suite(data, argv, envp, pipes);
	return (0);
}
