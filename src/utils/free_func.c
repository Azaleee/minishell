/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:47:24 by mosmont           #+#    #+#             */
/*   Updated: 2025/01/14 12:58:48 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tab(char **tab)
{
	char	**temp;

	temp = tab;
	while (tab && *tab)
	{
		free(*tab);
		tab++;
	}
	free(temp);
	temp = NULL;
	tab = NULL;
}

// void	free_all(t_minishell *minishell)
// {
// 	if (minishell->input)
// 		token_clear(minishell);
// 	if (minishell)
// 		free(minishell);
// }