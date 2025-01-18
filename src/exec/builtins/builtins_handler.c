/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:12:49 by mosmont           #+#    #+#             */
/*   Updated: 2025/01/19 00:40:35 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", 5) == 0)
		return (2);
	return (0);
}

void	execute_builtin(t_cmds *cmd, t_minishell *minishell, int builtin_id)
{
	(void)cmd;
	(void)minishell;
	if (builtin_id == 1)
		pwd();
	if (builtin_id == 2)
		print_env(minishell->env);
}
