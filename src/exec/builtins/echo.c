/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:17:23 by edetoh            #+#    #+#             */
/*   Updated: 2025/02/06 15:29:40 by edetoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	echo(t_args *args, char **env)
{
	int	new_line;
	int	n_counter;

	(void)env;
	new_line = 1;
	n_counter = 0;
	args = args->next;
	while (args)
	{
		if (ft_strncmp(args->arg, "-n", 2) == 0 && n_counter == 0)
		{
			new_line = 0;
			n_counter++;
		}
		else
		{
			ft_putstr_fd(args->arg, STDOUT_FILENO);
			if (args->next)
				ft_putstr_fd(" ", STDOUT_FILENO);
		}
		args = args->next;
	}
	if (new_line)
		ft_putstr_fd("\n", STDOUT_FILENO);
}
