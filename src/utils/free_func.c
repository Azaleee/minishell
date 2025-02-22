/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:47:24 by mosmont           #+#    #+#             */
/*   Updated: 2025/02/06 15:36:39 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return ;
	else
	{
		while (tab[i] != NULL)
		{
			free(tab[i]);
			tab[i] = NULL;
			i++;
		}
		free(tab);
		tab = NULL;
	}
}

void	exit_and_free(t_minishell *minishell, int exit_code)
{
	free_all(minishell);
	exit(exit_code);
}

void	free_after_exec(t_minishell *minishell)
{
	free_pipes(minishell, minishell->pipes);
	minishell->pipes = NULL;
	free(minishell->pid);
	minishell->pid = NULL;
}

void	free_all(t_minishell *minishell)
{
	if (!minishell)
		return ;
	if (minishell->pwd)
		free(minishell->pwd);
	if (minishell->input)
		token_clear(minishell);
	if (minishell->cmds)
		cmds_clear(&minishell->cmds);
	if (minishell->env)
		free_tab(minishell->env);
	if (minishell->pid)
		free(minishell->pid);
	if (minishell->pipes)
	{
		close_all_pipes(minishell);
		free_pipes(minishell, minishell->pipes);
		minishell->pipes = NULL;
	}
	if (minishell->heredoc_counter)
	{
		free(minishell->heredoc_counter);
		minishell->heredoc_counter = NULL;
	}
	free(minishell);
}
