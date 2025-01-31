/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:33:05 by mosmont           #+#    #+#             */
/*   Updated: 2025/01/31 21:00:50 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_path_cmd(char *cmd, char *path)
{
	int		i;
	char	**split_path;
	char	*current_path;
	char	*exec;

	i = 0;
	if (path == NULL || cmd == NULL)
		return (NULL);
	split_path = ft_split(path, ':');
	while (split_path[i])
	{
		current_path = ft_strjoin(split_path[i], "/");
		exec = ft_strjoin(current_path, cmd);
		if (access(exec, X_OK | F_OK) == 0)
		{
			free(current_path);
			free_tab(split_path);
			return (exec);
		}
		free(current_path);
		free(exec);
		i++;
	}
	free_tab(split_path);
	return (ft_strdup(cmd));
}

int	count_args_len(t_args *args)
{
	int	i;

	i = 0;
	while (args)
	{
		if (args->arg[0] != '\0')
			i++;
		args = args->next;
	}
	return (i);
}

char	**fill_cmd_tab(t_args *args)
{
	int		i;
	t_args	*init_pose;
	char	**arg_tab;

	i = 0;
	init_pose = args;
	arg_tab = NULL;
	i = count_args_len(args);
	if (i == 0)
		return (NULL);
	arg_tab = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (init_pose)
	{
		if (init_pose->arg[0] != '\0')
		{
			arg_tab[i] = ft_strdup(init_pose->arg);
			i++;
		}
		init_pose = init_pose->next;
	}
	arg_tab[i] = NULL;
	return (arg_tab);
}

void	check_access_cmd(t_minishell *minishell, char **cmd)
{
	struct stat	path_stat;

	if (access(cmd[0], F_OK) == -1)
	{
		if (errno == ENOENT)
			print_error(": No such file or directory", cmd, 127, minishell);
	}
	if (access(cmd[0], X_OK) == -1)
	{
		if (errno == EACCES)
			print_error(": Permission denied", cmd, 126, minishell);
	}
	if (stat(cmd[0], &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
		print_error(": Is a directory", cmd, 126, minishell);
}

void	parse_and_check_cmd(t_minishell *minishell, t_cmds *current, char **cmd)
{
	char	*env_value;

	env_value = get_env_value("PATH", minishell->env);
	current->path_cmd = get_path_cmd(cmd[0], env_value);
	free(env_value);
	if (ft_strchr(cmd[0], '/') != NULL)
		check_access_cmd(minishell, cmd);
	if (access(current->path_cmd, X_OK) == -1 || cmd[0][0] == '\0')
		print_error(": command not found", cmd, 127, minishell);
}
