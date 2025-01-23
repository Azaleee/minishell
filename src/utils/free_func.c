/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:47:24 by mosmont           #+#    #+#             */
/*   Updated: 2025/01/23 16:25:15 by edetoh           ###   ########.fr       */
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

void	free_all(t_minishell *minishell)
{
	if (!minishell)
		return ;
	if (minishell->input)
		token_clear(minishell);
	if (minishell->cmds)
		cmds_clear(minishell);
	if (minishell->env)
		free_tab(minishell->env);
	if (minishell->pid)
	{
		free(minishell->pid);
		minishell->pid = NULL;
	}
	if (minishell->pipes && minishell->nb_cmd > 1)
	{
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
