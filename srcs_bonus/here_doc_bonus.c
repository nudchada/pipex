/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nusamank <nusamank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 08:17:42 by nusamank          #+#    #+#             */
/*   Updated: 2024/05/01 11:34:26 by nusamank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	check_argc(int argc)
{
	if (argc < 5)
	{
		ft_putstr_fd("Incorrect number of arguments.\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

void	here_doc_input(char *limiter, int *pfd)
{
	char	*line;
	int		len;

	close(pfd[0]);
	while (1)
	{
		ft_putstr_fd("pipe heredoc> ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
		len = ft_strlen(line);
		line[len - 1] = '\0';
		if (!ft_strcmp(line, limiter))
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
		line[len - 1] = '\n';
		ft_putstr_fd(line, pfd[1]);
		free(line);
	}
}

void	here_doc_mode(int argc, char *limiter, char *outfile, int *pfd)
{
	int		out_fd;
	pid_t	pid;

	if (argc < 6)
	{
		ft_putstr_fd("Incorrect number of arguments.\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	out_fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (out_fd < 0)
		handle_errors(outfile);
	pid = fork();
	if (pid < 0)
		handle_errors(NULL);
	if (pid == 0)
	{
		here_doc_input(limiter, pfd);
	}
	else
	{
		close(pfd[1]);
		waitpid(pid, NULL, 0);
	}
}
