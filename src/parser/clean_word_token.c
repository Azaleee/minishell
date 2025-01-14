/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_word_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:37:14 by mosmont           #+#    #+#             */
/*   Updated: 2025/01/14 21:24:25 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_syntax_env_var(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c) || c == '_' || c == '?');
}

// pas oublier code erreur ?

char	*get_env_var(char *value, size_t *start)
{
	size_t	i;
	int		j;

	i = *start + 1;
	j = i;
	while (value[j] && check_syntax_env_var(value[j]))
		j++;
	if (j == i)
		return (NULL);
	if (value[j] == '?')
		return (ft_strdup(&value[j]));
	*start = j;
	return (ft_substr(value, i, j - i));
}

char	*get_env_value(char *env_var, char **env)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (strncmp(env_var, "?", 1) == 0)
		return (ft_itoa(0)); // IMPORTANT CHANGER
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

char	*replace_actual(char *value, char *env_value, char *env_var, size_t start)
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

char	*replace_env_var(char *value, char **env)
{
	char	*env_var;
	char	*env_value;
	size_t	i;
	size_t	start;

	i = 0;
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

void	clean_word_token(t_minishell *minishell, char **env)
{
	t_lexer	*current;

	current = minishell->input;
	while (current->token_type != T_EOF)
	{
		if (current->token_type == WORD)
		{
			current->value = replace_env_var(current->value, env);
			remove_quote(current->value);
		}
		printf("New value = %s\n", (char *)current->value);
		current = current->next;
	}
}
