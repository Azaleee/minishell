/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:53:48 by edetoh            #+#    #+#             */
/*   Updated: 2025/01/29 15:09:26 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_exit(t_minishell *minishell, int nb_commands)
{
	if (nb_commands > 1)
	{
		print_error(NULL, NULL, g_error_code, minishell);
		return (TRUE);
	}
	print_error("exit", NULL, g_error_code, minishell);
	return (TRUE);
}
