/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nusamank <nusamank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 18:17:50 by nusamank          #+#    #+#             */
/*   Updated: 2024/05/01 12:00:23 by nusamank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static char	**get_path_arr(char **envp)
{
	char	**path_arr;
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		handle_errors(NULL);
	path_arr = ft_split(envp[i] + 5, ':');
	return (path_arr);
}

char	*get_pathname(char **cmd, char **envp)
{
	char	**path_arr;
	char	*pathname;
	char	*temp;
	int		i;

	path_arr = get_path_arr(envp);
	i = 0;
	while (path_arr[i])
	{
		temp = ft_strjoin(path_arr[i], "/");
		pathname = ft_strjoin(temp, cmd[0]);
		free(temp);
		if (access(pathname, X_OK) == 0)
		{
			free_array(path_arr);
			return (pathname);
		}
		free(pathname);
		i++;
	}
	free_array(path_arr);
	return (NULL);
}

void	execute(char *argv, char **envp)
{
	char	**cmd;
	char	*pathname;

	cmd = ft_split(argv, ' ');
	pathname = get_pathname(cmd, envp);
	if (!pathname)
	{
		ft_putstr_fd("pipex: command not found: ", STDERR_FILENO);
		ft_putstr_fd(cmd[0], STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		free_array(cmd);
		exit(127);
	}
	if (execve(pathname, cmd, envp) < 0)
	{
		free(pathname);
		free_array(cmd);
		handle_errors(argv);
	}
}
