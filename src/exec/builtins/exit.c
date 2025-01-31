/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:53:48 by edetoh            #+#    #+#             */
/*   Updated: 2025/01/31 16:53:56 by edetoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	is_numeric_arg(const char *arg)
{
	if (*arg == '+' || *arg == '-')
		arg++;
	while (*arg)
	{
		if (!ft_isdigit(*arg))
			return (0);
		arg++;
	}
	return (1);
}

static void	exit_args(t_args *args, t_minishell *minishell)
{
	long	exit_code;

	if (args->arg)
	{
		if (is_numeric_arg(args->arg))
		{
			exit_code = ft_atol(args->arg);
			if (exit_code < 0)
				exit_code = 256 + (exit_code % 256);
			else
				exit_code = exit_code % 256;
			g_error_code = (int)exit_code;
		}
		else
		{
			print_error("exit", " : numeric argument required", 2, minishell);
		}
	}
}

int	ft_exit(t_minishell *minishell, int nb_commands)
{
	minishell->cmds->args = minishell->cmds->args->next;
	if (minishell->cmds->args && minishell->cmds->args->next)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_putstr_fd(" too many arguments\n", STDERR_FILENO);
		g_error_code = 1;
		return (TRUE);
	}
	if (minishell->cmds->args)
		exit_args(minishell->cmds->args, minishell);
	if (nb_commands > 1)
	{
		print_error(NULL, NULL, g_error_code, minishell);
		return (TRUE);
	}
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	print_error(NULL, NULL, g_error_code, minishell);
	return (TRUE);
}
