/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:28:27 by mosmont           #+#    #+#             */
/*   Updated: 2025/01/17 19:15:02 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	*get_next_cmd(void *node)
{
	return (((t_cmds *)node)->next);
}

void	*get_next_args(void *node)
{
	return (((t_args *)node)->next);
}

void	*get_next_token(void *node)
{
	return (((t_lexer *)node)->next);
}
