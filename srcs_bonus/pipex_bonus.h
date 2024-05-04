/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nusamank <nusamank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:38:01 by nusamank          #+#    #+#             */
/*   Updated: 2024/05/01 12:03:13 by nusamank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"
# include <errno.h>
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>

void	check_argc(int argc);
void	free_array(char **array);
void	handle_errors(char *message);
char	*get_pathname(char **cmd, char **envp);
void	execute(char *argv, char **envp);
void	open_outfile(char *outfile, int here_doc);
void	first_command(char *infile, int *pfd, char *cmd, char **envp);
int		last_command(int *pfd, char *cmd, char **envp);
int		ft_strcmp(const char *s1, const char *s2);
void	here_doc_mode(int argc, char *limiter, char *outfile, int *pfd);

#endif