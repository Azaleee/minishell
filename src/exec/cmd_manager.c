/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:33:05 by mosmont           #+#    #+#             */
/*   Updated: 2025/01/19 00:46:35 by mosmont          ###   ########.fr       */
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

char	**fill_cmd_tab(t_args *args)
{
	int		i;
	t_args	*init_pose;
	char	**arg_tab;

	i = 0;
	init_pose = args;
	arg_tab = NULL;
	while (args)
	{
		i++;
		args = args->next;
	}
	arg_tab = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (init_pose)
	{
		arg_tab[i] = init_pose->arg;
		i++;
		init_pose = init_pose->next;
	}
	arg_tab[i] = NULL;
	return (arg_tab);
}

void	check_access_cmd(t_minishell *minishell, char *path_cmd)
{
	struct stat path_stat;

	if (access(path_cmd, F_OK) == -1)
	{
		if (errno == ENOENT)
		{
			print_error("no such file or directory: ", path_cmd, 127, minishell);
			return;
		}
	}
	if (access(path_cmd, X_OK) == -1)
	{
		if (errno == EACCES)
		{
			print_error("permission denied: ", path_cmd, 126, minishell);
			return;
		}
	}
	if (stat(path_cmd, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
    {
        print_error("is a directory: ", path_cmd, 126, minishell);
        return;
    }
}

void	parse_and_check_cmd(t_minishell *minishell, t_cmds *current, char **cmd)
{
	// if (access(cmd[0], F_OK) == 0 || cmd[0][0] == '\0')
	// 	current->path_cmd = ft_strdup(cmd[0]);
	// else
	current->path_cmd = get_path_cmd(cmd[0],
			get_env_value("PATH", minishell->env));
	if (ft_strchr(cmd[0], '/') != NULL)
		check_access_cmd(minishell, cmd[0]);
	if (access(current->path_cmd, F_OK) == -1 || cmd[0][0] == '\0')
		print_error("command not found: ", cmd[0], 127, minishell);
}
