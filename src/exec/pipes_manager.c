/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:32:15 by mosmont           #+#    #+#             */
/*   Updated: 2025/02/06 15:37:19 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_pipes(t_minishell *minishell, int nb_cmd)
{
	int	i;

	i = 0;
	if (minishell->nb_cmd == 1)
		return ;
	minishell->pipes = malloc(sizeof(int *) * (nb_cmd - 1));
	if (!minishell->pipes)
		exit(EXIT_FAILURE);
	while (i < nb_cmd - 1)
	{
		minishell->pipes[i] = malloc(sizeof(int) * 2);
		if (pipe(minishell->pipes[i]) == -1)
		{
			printf("%d", i);
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	free_pipes(t_minishell *minishell, int **tab)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return ;
	else
	{
		while (i < minishell->nb_cmd - 1)
		{
			if (tab[i])
				free(tab[i]);
			i++;
		}
		free(tab);
		tab = NULL;
	}
}

void	close_all_pipes(t_minishell *minishell)
{
	int	i;

	i = 0;
	while (i < minishell->nb_cmd - 1)
	{
		close(minishell->pipes[i][0]);
		close(minishell->pipes[i][1]);
		i++;
	}
}

void	close_unused_pipes(t_minishell *minishell, int i)
{
	int	j;

	j = 0;
	while (j < minishell->nb_cmd - 1)
	{
		if (j != i - 1)
			close(minishell->pipes[j][0]);
		if (j != i)
			close(minishell->pipes[j][1]);
		j++;
	}
}
