/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 00:39:37 by mosmont           #+#    #+#             */
/*   Updated: 2025/01/21 12:40:26 by edetoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	print_env(char **env)
{
	int		i;
	char	*equal_pos;
	char	*value;

	i = 0;
	while (env[i])
	{
		equal_pos = ft_strchr(env[i], '=');
		if (equal_pos)
		{
			value = equal_pos + 1;
			if (ft_strncmp(value, "N/A", 3) != 0)
			{
				ft_putstr_fd(env[i], STDOUT_FILENO);
				ft_putstr_fd("\n", STDOUT_FILENO);
			}
		}
		i++;
	}
}
