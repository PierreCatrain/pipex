/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc_and_open.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 22:41:17 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/10 01:13:17 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	ft_complete(t_data_bonus *data, char **argv)
{
	char	*line;

	ft_putstr_fd("pipe heredoc> ", 1);
	line = get_next_line(0);
	if (ft_strncmp(line, argv[2], ft_strlen_gnl(argv[2])) == 1 \
			|| ft_strlen(argv[2]) != ft_strlen(line) - 1)
	{
		ft_putstr_fd(line, data->fd1);
		free(line);
		ft_complete(data, argv);
	}
	else
		free(line);
}

int	ft_get_str_here(char *str, t_data_bonus *data)
{
	int	index;

	index = 1;
	while (index <= 999)
	{
		data->str_index = ft_itoa(index);
		if (data->str_index == NULL)
			return (0);
		data->str_here = ft_strjoin(str, data->str_index);
		if (data->str_here == NULL)
			return (free(data->str_index), 0);
		if (access(data->str_here, 0) != 0)
			return (1);
		else
		{
			free(data->str_here);
			free(data->str_index);
		}
		index++;
	}
	return (0);
}

int	ft_here_doc(t_data_bonus *data, int argc, char **argv)
{
	if (ft_get_str_here(".here_doc", data) == 0)
		return (-1);
	data->fd1 = open(".here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (data->fd1 < 0)
		return (ft_putstr_fd("error with infile\n", 2), \
				free(data->str_here), free(data->str_index), -1);
	ft_complete(data, argv);
	close(data->fd1);
	data->fd1 = open(".here_doc", O_RDONLY, 0644);
	if (data->fd1 < 0)
	{
		unlink(".here_doc");
		free(data->str_here);
		free(data->str_index);
		return (ft_putstr_fd("error with infile\n", 2), -1);
	}
	unlink(".here_doc");
	free(data->str_here);
	free(data->str_index);
	data->fd2 = open(argv[argc - 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (data->fd2 < 0)
		return (ft_putstr_fd("error with outfile\n", 2), \
				ft_close_2_fd(*data, 1), -1);
	return (1);
}

int	ft_here_doc_and_open(t_data_bonus *data, int argc, \
		char **argv)
{
	if (ft_strncmp(argv[1], "here_doc", 8) == 0 && ft_strlen(argv[1]) == 8)
		return (ft_here_doc(data, argc, argv));
	else
	{
		data->fd1 = open(argv[1], O_RDONLY);
		if (data->fd1 < 0)
			return (ft_putstr_fd("error with infile\n", 2), -1);
		data->fd2 = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (data->fd2 < 0)
			return (ft_putstr_fd("error with outfile\n", 2), \
					ft_close_2_fd(*data, 1), -1);
	}
	return (0);
}
