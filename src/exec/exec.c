/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 12:49:35 by mosmont           #+#    #+#             */
/*   Updated: 2025/01/31 20:15:51 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_cmd(t_cmds *cmds)
{
	int	i;

	if (!cmds)
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
		{
			waitpid(minishell->pid[i], &status, 0);
			if (WIFEXITED(status))
				g_error_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				g_error_code = 128 + WTERMSIG(status);
		}
		i++;
	}
}

void	bultins_exe(int builtin_id_parent, int builtin_id, t_cmds *current, \
t_minishell *minishell)
{
	if (builtin_id)
	{
		execute_builtin_child(current, minishell, builtin_id);
		exit_and_free(minishell, 0);
	}
	if (builtin_id_parent)
	{
		execute_builtin_parent(current, minishell);
		exit_and_free(minishell, 0);
	}
}

void	execute_cmd(t_cmds *current, t_minishell *minishell, int i)
{
	char	**cmd;
	int		builtin_id;
	int		builtin_idparent;

	if (current->error_file == -1)
		exit_and_free(minishell, g_error_code);
	set_input_redir(current, minishell, i);
	set_output_redir(current, minishell, i);
	close_all_pipes(minishell);
	builtin_id = is_builtin(current->args->arg);
	if (builtin_id >= 5 && builtin_id <= 7)
	{
		execute_builtin_child(current, minishell, builtin_id);
		exit_and_free(minishell, 0);
	}
	else if (builtin_id >= 1 && builtin_id <= 4)
		exit_and_free(minishell, 0);
	cmd = fill_cmd_tab(current->args);
	if (cmd == NULL)
		exit_and_free(minishell, 0);
	parse_and_check_cmd(minishell, current, cmd);
	execve(current->path_cmd, cmd, minishell->env);
	perror("execve");
	free_all(minishell);
	free_tab(cmd);
	exit(1);
}

void	handle_sigint_cmd_exec(void)
{
	signal(SIGQUIT, handle_sigquit);
	signal(SIGINT, handle_sigint_cmd);
}

void	execute_all(t_minishell *minishell)
{
	int		i;
	t_cmds	*current_cmd;

	current_cmd = minishell->cmds;
	i = 0;
	minishell->nb_cmd = count_cmd(minishell->cmds);
	if (minishell->nb_cmd == 1
		&& execute_builtin_parent(minishell->cmds, minishell))
		return ;
	minishell->pid = (pid_t *)malloc(sizeof(pid_t) * minishell->nb_cmd);
	init_pipes(minishell, minishell->nb_cmd);
	while (current_cmd)
	{
		handle_sigint_cmd_exec();
		minishell->pid[i] = fork();
		if (minishell->pid[i] == 0)
			execute_cmd(current_cmd, minishell, i);
		i++;
		current_cmd = current_cmd->next;
	}
	close_all_pipes(minishell);
	wait_child(minishell);
	init_signals();
	free_after_exec(minishell);
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
