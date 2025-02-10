/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 11:13:03 by edetoh            #+#    #+#             */
/*   Updated: 2025/02/10 15:15:54 by edetoh           ###   ########.fr       */
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

static int	change_directory_and_update(char *path, \
	char ***env, int need_free_path)
{
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = getcwd(NULL, 0);
	if (chdir(path) == -1)
	{
		free(old_pwd);
		print_cd_error(path);
		if (need_free_path)
			free(path);
		return (g_error_code = 1, FALSE);
	}
	set_env_value("OLDPWD", old_pwd, env);
	free(old_pwd);
	new_pwd = getcwd(NULL, 0);
	set_env_value("PWD", new_pwd, env);
	free(new_pwd);
	if (need_free_path)
		free(path);
	return (g_error_code = 0, TRUE);
}

int	cd(t_args *args, char ***env)
{
	char	*path;
	int		need_free_path;

	need_free_path = 0;
	if (args->next && args->next->next)
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		return (g_error_code = 1, FALSE);
	}
	path = get_cd_path(args, *env);
	if (!path)
		return (g_error_code = 1, FALSE);
	if (args->next == NULL || (args->next && ft_strncmp(args->next->arg, \
	"-", 2) == 0))
		need_free_path = 1;
	return (change_directory_and_update(path, env, need_free_path));
}
