/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 16:38:17 by mosmont           #+#    #+#             */
/*   Updated: 2025/01/09 12:10:11 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	syntax_checker(char *msg_error, char *arg, char *line, int (*check)(char *))
{
	if ((*check)(line) == TRUE)
	{
		ft_putstr_fd(msg_error, 2);
		if (arg)
			ft_putstr_fd(arg, 2);
		return (TRUE);
	}
	return (FALSE);
}
