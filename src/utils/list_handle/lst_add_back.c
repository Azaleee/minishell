/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_add_back.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:47:25 by mosmont           #+#    #+#             */
/*   Updated: 2025/01/17 19:22:24 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	lst_add_back(void **lst, void *new_node, void *(*get_next)(void *),
		void (*set_next)(void *, void *))
{
	void	*current;

	if (!new_node)
		return ;
	if (*lst == NULL)
	{
		*lst = new_node;
		return ;
	}
	current = *lst;
	while (get_next(current))
	{
		current = get_next(current);
	}
	set_next(current, new_node);
}
