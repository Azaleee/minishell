/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 19:27:46 by mosmont           #+#    #+#             */
/*   Updated: 2024/10/23 12:29:56 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!new)
		return ;
	new->next = *lst;
	*lst = new;
}
// int	main(void)
// {
// 	t_list	*lst;

// 	lst = ft_lstnew("salut ");
// 	lst->next = ft_lstnew("je suis ");
// 	ft_lstadd_front(&lst, ft_lstnew("a 42 !"));
// 	while (lst)
// 	{
// 		printf("%s", (char *)lst->content);
// 		lst = lst->next;
// 	}
// 	return (0);
// }
