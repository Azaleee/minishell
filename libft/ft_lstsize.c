/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 19:41:10 by mosmont           #+#    #+#             */
/*   Updated: 2024/10/16 18:56:23 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		result;
	t_list	*current;

	if (!lst)
		return (0);
	result = 0;
	current = lst;
	while (current != NULL)
	{
		current = current->next;
		result++;
	}
	return (result);
}
