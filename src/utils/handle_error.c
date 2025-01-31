/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 16:38:17 by mosmont           #+#    #+#             */
/*   Updated: 2025/01/31 20:53:44 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	syntax_checker(char *msg_error, char *arg, char *line, int (*check)(char *))
{
	if ((*check)(line) == TRUE)
	{
		ft_putstr_fd(msg_error, 2);
		if (arg)
			ft_putstr_fd(arg, 2);
		return (TRUE);
	}
	return (FALSE);
}

int	print_error(char *message, char **cmd, int exit_code,
	t_minishell *minishell)
{
	if (cmd)
		write(STDERR_FILENO, cmd[0], ft_strlen(cmd[0]));
	if (message)
		write(STDERR_FILENO, message, ft_strlen(message));
	if (message || cmd)
		write(STDERR_FILENO, "\n", 1);
	if (cmd)
		free_tab(cmd);
	free_all(minishell);
	exit(exit_code);
}
