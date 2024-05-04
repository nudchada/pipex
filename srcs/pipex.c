/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nusamank <nusamank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:12:14 by nusamank          #+#    #+#             */
/*   Updated: 2024/04/30 15:35:49 by nusamank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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

int	last_command(char *outfile, int *pfd, char *cmd, char **envp)
{
	pid_t	pid;
	int		out_fd;
	int		status;

	pid = fork();
	if (pid < 0)
		handle_errors(NULL);
	if (pid == 0)
	{
		out_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (out_fd < 0)
			handle_errors(outfile);
		if (dup2(out_fd, STDOUT_FILENO) < 0)
			handle_errors(NULL);
		close(out_fd);
		if (dup2(pfd[0], STDIN_FILENO) < 0)
			handle_errors(NULL);
		close(pfd[0]);
		execute(cmd, envp);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
		return (EXIT_FAILURE);
}

int	main(int argc, char **argv, char **envp)
{
	int		pfd[2];
	int		status;

	if (argc != 5)
	{
		ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 outfile.\n", 2);
		exit(EXIT_FAILURE);
	}
	if (pipe(pfd) < 0)
		handle_errors(NULL);
	first_command(argv[1], pfd, argv[2], envp);
	status = last_command(argv[4], pfd, argv[3], envp);
	waitpid(-1, NULL, 0);
	return (status);
}
