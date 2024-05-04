/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nusamank <nusamank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 10:23:28 by nusamank          #+#    #+#             */
/*   Updated: 2024/05/01 12:01:48 by nusamank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	open_outfile(char *outfile, int here_doc)
{
	int		out_fd;

	if (here_doc)
		out_fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		out_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out_fd < 0)
		handle_errors(outfile);
	if (dup2(out_fd, STDOUT_FILENO) < 0)
		handle_errors(NULL);
	close(out_fd);
}

void	first_command(char *infile, int *pfd, char *cmd, char **envp)
{
	pid_t	pid;
	int		in_fd;

	pid = fork();
	if (pid < 0)
		handle_errors(NULL);
	if (pid == 0)
	{
		close(pfd[0]);
		in_fd = open(infile, O_RDONLY);
		if (in_fd < 0)
			handle_errors(infile);
		if (dup2(in_fd, STDIN_FILENO) < 0)
			handle_errors(NULL);
		close(in_fd);
		if (dup2(pfd[1], STDOUT_FILENO) < 0)
			handle_errors(NULL);
		execute(cmd, envp);
	}
	close(pfd[1]);
}

void	middle_command(int *pfd, char *cmd, char **envp)
{
	pid_t	pid;
	int		pfd2[2];

	if (pipe(pfd2) < 0)
		handle_errors(NULL);
	pid = fork();
	if (pid < 0)
		handle_errors(NULL);
	if (pid == 0)
	{
		close(pfd2[0]);
		if (dup2(pfd[0], STDIN_FILENO) < 0)
			handle_errors(NULL);
		if (dup2(pfd2[1], STDOUT_FILENO) < 0)
			handle_errors(NULL);
		execute(cmd, envp);
	}
	close(pfd[0]);
	close(pfd2[1]);
	pfd[0] = pfd2[0];
}

int	last_command(int *pfd, char *cmd, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		handle_errors(NULL);
	if (pid == 0)
	{
		if (dup2(pfd[0], STDIN_FILENO) < 0)
			handle_errors(NULL);
		close(pfd[0]);
		execute(cmd, envp);
	}
	close(pfd[0]);
	close(pfd[1]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
		return (EXIT_FAILURE);
}

int	main(int argc, char **argv, char **envp)
{
	int		i;
	int		pfd[2];
	int		status;
	int		here_doc;

	check_argc(argc);
	here_doc = 0;
	if (pipe(pfd) < 0)
		handle_errors(NULL);
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		here_doc = 1;
		here_doc_mode(argc, argv[2], argv[argc - 1], pfd);
	}
	else
		first_command(argv[1], pfd, argv[2], envp);
	i = 3;
	while (i < argc - 2)
		middle_command(pfd, argv[i++], envp);
	open_outfile(argv[argc - 1], here_doc);
	status = last_command(pfd, argv[i], envp);
	while (waitpid(-1, NULL, 0) > 0)
		continue ;
	return (status);
}
