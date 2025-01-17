/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:05:59 by mosmont           #+#    #+#             */
/*   Updated: 2025/01/17 19:29:53 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_value(char *env_var, char **env)
{
	int		i;

	i = 0;
	if (strncmp(env_var, "?", 1) == 0)
		return (ft_itoa(g_error_code));
	while (env[i])
	{
		if (ft_strncmp(env[i], env_var, ft_strlen(env_var)) == 0
			&& env[i][ft_strlen(env_var)] == '=')
		{
			return (env[i] + ft_strlen(env_var) + 1);
		}
		i++;
	}
	return (NULL);
}

char	**env_cpy(char **env)
{
	int		i;
	char	**new_env;

	i = 0;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}
