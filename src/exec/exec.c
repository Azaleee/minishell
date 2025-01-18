/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 12:49:35 by mosmont           #+#    #+#             */
/*   Updated: 2025/01/18 23:37:46 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_cmd(t_cmds *cmds)
{
	int	i;

	if (!cmds || cmds->args->arg == NULL)
		return (0);
	i = 0;
	while (cmds)
	{
		i++;
		cmds = cmds->next;
	}
	return (i);
}

void	wait_child(t_minishell *minishell)
{
	int	i;
	int	status;

	i = 0;
	while (i < minishell->nb_cmd)
	{
		if (minishell->pid[i] > 0)
			waitpid(minishell->pid[i], &status, 0);
		if (WIFEXITED(status))
			g_error_code = WEXITSTATUS(status);
		i++;
	}
}

void	execute_cmd(t_cmds *current, t_minishell *minishell, int i)
{
	char	**cmd;
	int		builtin_id;

	// printf("Executing command %d\n", i);
	if (current->error_file == -1)
		exit(1);
	set_input_redir(current, minishell, i);
	set_output_redir(current, minishell, i);
	close_unused_pipes(minishell, i);
	builtin_id = is_builtin(current->args->arg);
	if (builtin_id)
	{
		execute_builtin(current, minishell, builtin_id);
		free(minishell->pid);
		free_pipes(minishell, minishell->pipes);
		free_all(minishell);
		exit(0);
	}
	cmd = fill_cmd_tab(current->args);
	parse_and_check_cmd(minishell, current, cmd);
	execve(current->path_cmd, cmd, minishell->env);
	perror("execve");
}

void	execute_all(t_minishell *minishell)
{
	int		i;
	t_cmds	*current_cmd;

	i = 0;
	minishell->nb_cmd = count_cmd(minishell->cmds);
	minishell->pid = (pid_t *)malloc(sizeof(pid_t) * minishell->nb_cmd);
	current_cmd = minishell->cmds;
	init_pipes(minishell, minishell->nb_cmd);
	while (current_cmd)
	{
		minishell->pid[i] = fork();
		if (minishell->pid[i] == 0)
			execute_cmd(current_cmd, minishell, i);
		else if (minishell->pid[i] < 0)
			perror("fork");
		i++;
		current_cmd = current_cmd->next;
	}
	close_all_pipes(minishell);
	wait_child(minishell);
	free_pipes(minishell, minishell->pipes);
	free(minishell->pid);
}

// void	execute_all(t_minishell *minishell)
// {
// 	int		i;
// 	t_cmds	*current_cmd;
// 	t_cmds	*cmd_array[minishell->nb_cmd];

// 	minishell->nb_cmd = count_cmd(minishell->cmds);
// 	minishell->pid = (pid_t *)malloc(sizeof(pid_t) * minishell->nb_cmd);

// 	Stocker les commandes dans un tableau pour un accès inverse
// 	current_cmd = minishell->cmds;
// 	for (i = 0; i < minishell->nb_cmd; i++)
// 	{
// 		cmd_array[i] = current_cmd;
// 		current_cmd = current_cmd->next;
// 	}

// 	init_pipes(minishell, minishell->nb_cmd);
// 	i = minishell->nb_cmd - 1; // Initialiser i à nb_cmd - 1
// 	while (i >= 0)
// 	{
// 		minishell->pid[i] = fork();
// 		if (minishell->pid[i] == 0)
// 		{
// 			execute_cmd(cmd_array[i], minishell, i);
// 		}
// 		i--; // Décrémenter i à chaque itération
// 	}
// 	close_all_pipes(minishell);
// 	wait_child(minishell);
// 	free_pipes(minishell, minishell->pipes);
// 	free(minishell->pid);
// }
