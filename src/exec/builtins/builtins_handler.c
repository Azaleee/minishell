/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:12:49 by mosmont           #+#    #+#             */
/*   Updated: 2025/01/31 20:16:43 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "cd", 2) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (2);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (3);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (4);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (5);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (6);
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (7);
	return (0);
}

void	execute_builtin_child(t_cmds *cmd, t_minishell *minishell
			, int builtin_id)
{
	(void)cmd;
	if (builtin_id == 5)
		pwd();
	if (builtin_id == 6)
		print_env(minishell->env);
	if (builtin_id == 7)
		echo(cmd->args, minishell->env);
}

int	execute_builtin_parent(t_cmds *cmd, t_minishell *minishell)
{
	int		builtin_id;

	(void)cmd;
	if (!minishell->cmds->args)
		return (0);
	builtin_id = is_builtin(minishell->cmds->args->arg);
	if (builtin_id == 1)
		cd(minishell->cmds->args, &minishell->env);
	else if (builtin_id == 2)
		ft_export(minishell->cmds->args, &minishell->env);
	else if (builtin_id == 3)
		unset(minishell->cmds->args, &minishell->env);
	else if (builtin_id == 4)
		ft_exit(minishell, minishell->nb_cmd);
	else
		return (0);
	return (1);
}
