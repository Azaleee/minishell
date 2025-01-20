/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:23:35 by edetoh            #+#    #+#             */
/*   Updated: 2025/01/20 18:48:55 by edetoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

//TODO : NORME

static int	is_valid_identifier(char *str)
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

static void	print_export_error(char *arg)
{
	ft_putstr_fd("export: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

static void	sort_env(char **env)
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

static void	print_sorted_env(char **env)
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
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			ft_putstr_fd(var_name, STDOUT_FILENO);
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(var_value, STDOUT_FILENO);
			ft_putstr_fd("\"\n", STDOUT_FILENO);
			free(var_name);
		}
		i++;
	}
}

int	ft_export(t_args *args, char ***env)
{
	char	*env_var;
	char	*env_value;
	char	*equal_pos;
	int		status;

	args = args->next;
	if (!args)
	{
		print_sorted_env(*env);
		return (TRUE);
	}
	status = TRUE;
	while (args)
	{
		if (!is_valid_identifier(args->arg))
		{
			print_export_error(args->arg);
			status = FALSE;
		}
		else
		{
			equal_pos = ft_strchr(args->arg, '=');
			if (equal_pos)
			{
				env_var = ft_substr(args->arg, 0, equal_pos - args->arg);
				env_value = equal_pos + 1;
				set_env_value(env_var, env_value, env);
				free(env_var);
			}
		}
		args = args->next;
	}
	return (status);
}
