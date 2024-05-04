/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nusamank <nusamank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 18:17:50 by nusamank          #+#    #+#             */
/*   Updated: 2024/04/30 13:57:18 by nusamank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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

static void	put_error_message(char *message)
{
	char	buf[1024];
	size_t	len;

	buf[0] = '\0';
	len = 0;
	len += ft_strlcat(buf, "pipex: ", sizeof(buf) - len - 1);
	len += ft_strlcat(buf, strerror(errno), sizeof(buf) - len - 1);
	len += ft_strlcat(buf, ": ", sizeof(buf) - len - 1);
	len += ft_strlcat(buf, message, sizeof(buf) - len - 1);
	ft_strlcat(buf, "\n", sizeof(buf) - len - 1);
	ft_putstr_fd(buf, STDERR_FILENO);
}

void	handle_errors(char *message)
{
	if (message)
		put_error_message(message);
	else
		perror("pipex");
	exit(EXIT_FAILURE);
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
