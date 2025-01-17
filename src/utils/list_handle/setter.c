/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:26:34 by mosmont           #+#    #+#             */
/*   Updated: 2025/01/17 19:15:25 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	set_next_cmd(void *node, void *next)
{
	((t_cmds *)node)->next = next;
}

void	set_next_args(void *node, void *next)
{
	((t_args *)node)->next = (t_args *)next;
}

void	set_next_token(void *node, void *next)
{
	((t_lexer *)node)->next = (t_lexer *)next;
}
