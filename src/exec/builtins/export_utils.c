/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:35:24 by edetoh            #+#    #+#             */
/*   Updated: 2025/01/21 12:39:35 by edetoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (FALSE);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void	print_export_error(char *arg)
{
	ft_putstr_fd("export: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

void	sort_env(char **env)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (env[i])
	{
		j = i + 1;
		while (env[j])
		{
			if (ft_strncmp(env[i], env[j], ft_strlen(env[i])) > 0)
			{
				temp = env[i];
				env[i] = env[j];
				env[j] = temp;
			}
			j++;
		}
		i++;
	}
}

static void	print_var_value(char *var_name, char *var_value)
{
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd(var_name, STDOUT_FILENO);
	if (ft_strncmp(var_value, "N/A", 3) != 0)
	{
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(var_value, STDOUT_FILENO);
		ft_putstr_fd("\"", STDOUT_FILENO);
	}
	ft_putstr_fd("\n", STDOUT_FILENO);
}

void	print_sorted_env(char **env)
{
	int		i;
	char	*equal_pos;
	char	*var_name;
	char	*var_value;

	sort_env(env);
	i = 0;
	while (env[i])
	{
		equal_pos = ft_strchr(env[i], '=');
		if (equal_pos)
		{
			var_name = ft_substr(env[i], 0, equal_pos - env[i]);
			var_value = equal_pos + 1;
			print_var_value(var_name, var_value);
			free(var_name);
		}
		i++;
	}
}
