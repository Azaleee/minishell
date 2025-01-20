/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 11:13:03 by edetoh            #+#    #+#             */
/*   Updated: 2025/01/20 14:05:13 by edetoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	print_cd_error(char *path)
{
	ft_putstr_fd("cd: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

int	cd(t_args *args, char ***env)
{
	char	*path;
	char	*pwd;

	args = args->next;
	if (!args || !args->arg)
	{
		path = get_env_value("HOME", *env);
		if (!path)
			return (ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO), FALSE);
	}
	else
		path = args->arg;
	if (ft_strncmp(path, "-", 2) == 0)
	{
		path = get_env_value("OLDPWD", *env);
		if (!path)
			return (ft_putstr_fd("cd: OLDPWD not set\n", STDERR_FILENO), FALSE);
	}
	pwd = getcwd(NULL, 0);
	if (chdir(path) == -1)
		return (free(pwd), print_cd_error(path), FALSE);
	set_env_value("OLDPWD", pwd, env);
	free(pwd);
	pwd = getcwd(NULL, 0);
	set_env_value("PWD", path, env);
	free(pwd);
	return (TRUE);
}

