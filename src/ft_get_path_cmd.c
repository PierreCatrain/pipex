/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:49:35 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/09 23:05:23 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	ft_strlen(char *str)
{
	int	count;

	count = 0;
	while (str[count])
		count++;
	return (count);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*join;
	size_t	i;
	size_t	j;

	join = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (join == NULL)
		return (0);
	i = 0;
	j = 0;
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		join[i + j] = s2[j];
		j++;
	}
	join[i + j] = '\0';
	return (join);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}

char	*find_path(char **envp)
{
	int	i;

	i = 0;
	while (ft_strncmp("PATH=", envp[i], 5) == 1)
		i++;
	return (&envp[i][5]);
}

char	*ft_get_path_cmd(char *command, char **envp)
{
	char	*str;
	char	**path_env;
	char	*tempo;
	char	*path_command;
	int		i;

	str = find_path(envp);
	path_env = ft_split(str, ':');
	if (path_env == NULL)
		return (NULL);
	i = -1;
	while (path_env[++i])
	{
		tempo = ft_strjoin(path_env[i], "/");
		if (tempo == NULL)
			return (free_2d(path_env), NULL);
		path_command = ft_strjoin(tempo, command);
		if (path_command == NULL)
			return (free(tempo), free_2d(path_env), NULL);
		free(tempo);
		if (access(path_command, 0) == 0)
			return (free_2d(path_env), path_command);
		free(path_command);
	}
	return (free_2d(path_env), NULL);
}
