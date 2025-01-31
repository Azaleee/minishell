/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:17:23 by edetoh            #+#    #+#             */
/*   Updated: 2025/01/31 19:07:12 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	echo(t_args *args, char **env)
{
	int	new_line;

	(void)env;
	new_line = 1;
	args = args->next;
	while (args)
	{
		if (ft_strncmp(args->arg, "-n", 2) == 0)
			new_line = 0;
		else
		{
			ft_putstr(args->arg);
			if (args->next)
				ft_putstr_fd(" ", STDOUT_FILENO);
		}
		args = args->next;
	}
	if (new_line)
		ft_putstr_fd("\n", STDOUT_FILENO);
}
