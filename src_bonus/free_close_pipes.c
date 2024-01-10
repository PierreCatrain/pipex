/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_close_pipes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 01:32:15 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/10 02:06:17 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	close_fail_pipe(int **pipes, int index)
{
	index--;
	while (index >= 0)
	{
		close(pipes[index][0]);
		close(pipes[index][1]);
		index--;
	}
}

void	free_pipes(int **pipes, int index)
{
	while (--index >= 0)
		free(pipes[index]);
	free(pipes);
}

void	init_error_1(t_data_bonus data, int **pipes, int i)
{
	ft_putstr_fd("Erreur d'allocation de mémoire pour les pipes", 2);
	close_fail_pipe(pipes, i);
	free_pipes(pipes, i);
	ft_close_bonus(data, pipes, 3);
	exit(EXIT_FAILURE);
}

void	init_error_2(t_data_bonus data, int **pipes, int i)
{
	ft_putstr_fd("Erreur de création des pipes", 2);
	close_fail_pipe(pipes, i);
	free_pipes(pipes, i + 1);
	ft_close_bonus(data, pipes, 3);
	exit(EXIT_FAILURE);
}
