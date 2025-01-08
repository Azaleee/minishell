/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:35:27 by mosmont           #+#    #+#             */
/*   Updated: 2025/01/07 22:13:19 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;
	void	*new_content;

	new_list = NULL;
	while (lst != NULL)
	{
		new_content = (*f)(lst->content);
		new_node = ft_lstnew(new_content);
		if (new_node == NULL)
		{
			ft_lstclear(&new_list, (*del));
			if (new_content)
				(*del)(new_content);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}
// static void	*f_lst(void *content)
// {
// 	int		i;
// 	char	*str;
// 	char	*nstr;

// 	i = 0;
// 	str = (char *)content;
// 	nstr = malloc(sizeof(char) * ft_strlen(str) + 1);
// 	while (str[i])
// 	{
// 		nstr[i] = str[i] + 1;
// 		i++;
// 	}
// 	nstr[i] = '\0';
// 	return (nstr);
// }

// static void	del_lst(void *content)
// {
// 	free(content);
// }

// int	main(void)
// {
// 	t_list	*lst;
// 	t_list	*new_list;
// 	t_list	*temp;

// 	lst = ft_lstnew(ft_strndup("abc"));
// 	lst->next = ft_lstnew(ft_strndup("def"));
// 	new_list = ft_lstmap(lst, &f_lst, &del_lst);
// 	temp = new_list;
// 	while (temp)
// 	{
// 		printf("%s", (char *)temp->content);
// 		temp = temp->next;
// 	}
// 	ft_lstclear(&lst, &del_lst);
// 	ft_lstclear(&new_list, &del_lst);
// 	return (0);
// }