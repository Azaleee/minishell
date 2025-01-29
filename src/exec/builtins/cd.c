/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 11:13:03 by edetoh            #+#    #+#             */
/*   Updated: 2025/01/29 16:36:17 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	print_cd_error(char *path)
{
	ft_putstr_fd("cd: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

static char	*get_cd_path(t_args *args, char **env)
{
	char	*path;

	args = args->next;
	if (!args || !args->arg)
	{
		path = get_env_value("HOME", env);
		if (!path)
		{
			ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
			return (NULL);
		}
	}
	else if (ft_strncmp(args->arg, "-", 2) == 0)
	{
		path = get_env_value("OLDPWD", env);
		if (!path)
		{
			ft_putstr_fd("cd: OLDPWD not set\n", STDERR_FILENO);
			return (NULL);
		}
	}
	else
		path = args->arg;
	return (path);
}

int	cd(t_args *args, char ***env)
{
	char	*path;
	char	*pwd;

	path = get_cd_path(args, *env);
	if (!path)
		return (FALSE);
	pwd = getcwd(NULL, 0);
	if (chdir(path) == -1)
	{
		free(pwd);
		print_cd_error(path);
		return (FALSE);
	}
	set_env_value("OLDPWD", pwd, env);
	free(pwd);
	pwd = getcwd(NULL, 0);
	set_env_value("PWD", pwd, env);
	free(pwd);
	free(path);
	return (TRUE);
}
