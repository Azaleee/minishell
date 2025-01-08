/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 20:04:24 by mosmont           #+#    #+#             */
/*   Updated: 2025/01/07 18:24:29 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current;

	if (!new || !lst)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current->next != NULL)
		current = current->next;
	current->next = new;
}
// int	main(void)
// {
// 	t_list	*lst;

// 	lst = ft_lstnew("salut ");
// 	lst->next = ft_lstnew("je suis ");
// 	ft_lstadd_back(&lst, ft_lstnew("a 42 !"));
// 	while (lst)
// 	{
// 		printf("%s", (char *)lst->content);
// 		lst = lst->next;
// 	}
// 	return (0);
// }