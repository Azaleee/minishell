/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:23:35 by edetoh            #+#    #+#             */
/*   Updated: 2025/01/21 12:35:35 by edetoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	handle_export_arg(char *arg, char ***env)
{
	char	*env_var;
	char	*env_value;
	char	*equal_pos;

	if (!is_valid_identifier(arg))
	{
		print_export_error(arg);
		return (FALSE);
	}
	equal_pos = ft_strchr(arg, '=');
	if (equal_pos)
	{
		env_var = ft_substr(arg, 0, equal_pos - arg);
		env_value = equal_pos + 1;
		set_env_value(env_var, env_value, env);
		free(env_var);
	}
	else
		set_env_value(arg, "N/A", env);
	return (TRUE);
}

int	ft_export(t_args *args, char ***env)
{
	int	status;

	args = args->next;
	if (!args)
		return (print_sorted_env(*env), TRUE);
	status = TRUE;
	while (args)
	{
		if (!handle_export_arg(args->arg, env))
			status = FALSE;
		args = args->next;
	}
	return (status);
}
