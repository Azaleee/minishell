/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:17:23 by edetoh            #+#    #+#             */
/*   Updated: 2025/01/24 12:03:31 by edetoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	putstr_env(char *str, char **env)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	if (str[0] == '$' && ft_isprint(str[1]))
	{
		while (env[i])
		{
			if (str[0] == '$' && str[1] == '?')
				return (ft_putnbr_fd(g_error_code, STDOUT_FILENO), 0);
			if (ft_strncmp(env[i], str + 1, ft_strlen(str + 1)) == 0)
			{
				j = ft_strlen(str);
				if (env[i][j] == '=')
					j++;
				value = ft_strdup(env[i] + j);
				ft_putstr_fd(value, STDOUT_FILENO);
				return (free(value), 0);
			}
			i++;
		}
	}
	return (ft_putstr_fd(str, STDOUT_FILENO), 0);
}

void	echo(t_args *args, char **env)
{
	int	new_line;

	new_line = 1;
	args = args->next;
	while (args)
	{
		if (ft_strncmp(args->arg, "-n", 2) == 0)
			new_line = 0;
		else
		{
			putstr_env(args->arg, env);
			if (args->next)
				ft_putstr_fd(" ", STDOUT_FILENO);
		}
		args = args->next;
	}
	if (new_line)
		ft_putstr_fd("\n", STDOUT_FILENO);
}
