/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:56:35 by mosmont           #+#    #+#             */
/*   Updated: 2025/01/17 19:30:44 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_var(char *value, size_t *start)
{
	size_t	i;
	size_t	j;

	i = *start + 1;
	j = i;
	while (value[j] && check_syntax_env_var(value[j]))
		j++;
	if (j == i)
		return (NULL);
	*start = j;
	if (value[j] == '?')
		return (ft_strdup(&value[j]));
	return (ft_substr(value, i, j - i));
}

char	*expand_env_var(char *value, char **env, size_t i)
{
	char	*env_var;
	char	*env_value;
	size_t	start;

	while (value[i])
	{
		if (value[i] == '$' && (if_in_quote(value, &i) == '"'
				|| !if_in_quote(value, &i)) && value[i + 1] != '$')
		{
			start = i;
			env_var = get_env_var(value, &i);
			if (!env_var)
			{
				i++;
				continue ;
			}
			env_value = get_env_value(env_var, env);
			value = replace_actual(value, env_value, env_var, start);
			i = start + ft_strlen(env_value);
		}
		else
			i++;
	}
	return (value);
}

char	*replace_actual(char *value, char *env_value, char *env_var,
		size_t start)
{
	char	*temp;
	char	*new_str;
	char	*start_of_str;
	size_t	env_var_l;

	env_var_l = ft_strlen(env_var);
	start_of_str = ft_substr(value, 0, start);
	temp = ft_strjoin(start_of_str, env_value);
	new_str = ft_strjoin(temp, &value[start + env_var_l + 1]);
	free(temp);
	free(value);
	free(start_of_str);
	free(env_var);
	return (new_str);
}

int	check_syntax_env_var(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c) || c == '_' || c == '?');
}
