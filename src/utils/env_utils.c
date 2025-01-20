/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:05:59 by mosmont           #+#    #+#             */
/*   Updated: 2025/01/20 11:11:14 by edetoh           ###   ########.fr       */
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

char	**add_env_value(char *env_var, char *env_value, char **env)
{
	int		i;
	char	**new_env;
	char	*new_entry;
	char	*temp;

	i = 0;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		new_env[i] = env[i];
		i++;
	}
	temp = ft_strjoin(env_var, "=");
	new_entry = ft_strjoin(temp, env_value);
	free(temp);
	new_env[i] = new_entry;
	new_env[i + 1] = NULL;
	return (new_env);
}

int	set_env_value(char *env_var, char *env_value, char **env)
{
	int		i;
	char	**new_env;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], env_var, ft_strlen(env_var)) == 0
			&& env[i][ft_strlen(env_var)] == '=')
		{
			free(env[i]);
			env[i] = ft_strjoin(env_var, env_value);
			return (TRUE);
		}
		i++;
	}
	new_env = add_env_value(env_var, env_value, env);
	if (!new_env)
		return (FALSE);
	free(env);
	env = new_env;
	return (TRUE);
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
