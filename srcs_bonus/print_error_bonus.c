/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nusamank <nusamank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 11:58:54 by nusamank          #+#    #+#             */
/*   Updated: 2024/05/01 12:12:43 by nusamank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
