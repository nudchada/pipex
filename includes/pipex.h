/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nusamank <nusamank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:33:00 by nusamank          #+#    #+#             */
/*   Updated: 2024/04/30 13:59:16 by nusamank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"
# include <errno.h>
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>

void	free_array(char **array);
void	handle_errors(char *message);
char	*get_pathname(char **cmd, char **envp);
void	execute(char *argv, char **envp);
void	first_command(char *infile, int *pfd, char *cmd, char **envp);
int		last_command(char *outfile, int *pfd, char *cmd, char **envp);

#endif