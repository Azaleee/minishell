/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 12:49:35 by mosmont           #+#    #+#             */
/*   Updated: 2025/01/16 22:51:56 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_cmd(t_cmds *cmds)
{
	int	i;

	if (!cmds && cmds->args->arg == NULL)
		return (0);
	i = 0;
	while (cmds)
	{
		i++;
		cmds = cmds->next;
	}
	return (i);
}

void	init_pipes(t_minishell *minishell, int nb_cmd)
{
	int	i;

	i = 0;
	minishell->pipes = malloc(sizeof(int *) * (nb_cmd - 1));
	if (!minishell->pipes)
		exit(EXIT_FAILURE);
	while (i < nb_cmd - 1)
	{
		minishell->pipes[i] = malloc(sizeof(int) * 2);
		if (pipe(minishell->pipes[i]) == -1)
		{
			printf("%d", i);
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

char	**fill_cmd_tab(t_args *args)
{
	int	i;
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

void	free_split(char **tab)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return ;
	else
	{
		while (tab[i] != NULL)
		{
			free(tab[i]);
			i++;
		}
		free(tab);
		tab = NULL;
	}
}

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
			free_split(split_path);
			return (exec);
		}
		free(current_path);
		free(exec);
		i++;
	}
	free_split(split_path);
	return (ft_strdup(cmd));
}

char	*ft_get_path(char **env)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			while (env[i][j] != '\0')
				j++;
			break ;
		}
		i++;
	}
	if (j == 0)
		return (NULL);
	return (env[i] + 5 + 1);
}

void	free_pipes(t_minishell *minishell, int **tab)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return ;
	else
	{
		while (i < minishell->nb_cmd - 1)
		{
			if (tab[i])
				free(tab[i]);
			i++;
		}
		free(tab);
		tab = NULL;
	}
}

int	print_error(char *message, char **cmd, int exit_code, t_minishell *minishell)
{
	char	*arg;

	arg = *cmd;
	write(STDERR_FILENO, message, ft_strlen(message));
	if (arg != NULL)
		write(STDERR_FILENO, arg, ft_strlen(arg));
	write(STDERR_FILENO, "\n", 1);
	free(minishell->pid);
	free_pipes(minishell, minishell->pipes);
	// free(minishell->cmds->path_cmd);
	// if (cmd)
	// 	free_tab(cmd);
	free_all(minishell);
	free(cmd);
	exit(exit_code);
}

void	check_access_cmd(t_minishell *minishell, char *path_cmd)
{
	if (access(path_cmd, X_OK) == -1)
	{
		if (errno == EACCES)
			print_error("permission denied: ", &path_cmd, 126, minishell);
		else if (errno == ENOENT)
			print_error("no such file or directory: ",
				&path_cmd, 127, minishell);
	}
}

void	parse_and_check_cmd(t_minishell *minishell, t_cmds *current, char **cmd)
{
	current->path_cmd = get_path_cmd(cmd[0], ft_get_path(minishell->env));
	// fprintf(stderr, "cmd path -> %s\n", current->path_cmd);
	if (ft_strncmp(cmd[0], "./", 2) == 0
		|| ft_strchr(cmd[0], '/') != NULL)
		check_access_cmd(minishell, current->path_cmd);
	if (access(current->path_cmd, F_OK) == -1)
		print_error("command not found: ", cmd, 127, minishell);
}

int	open_file(char *file, int mode, int append_mode)
{
	int	fd;

	if (mode == 0)
		fd = open(file, O_RDONLY);
	else if (mode == 1)
	{
		if (append_mode == 0)
			fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else
		return (-1);
	return (fd);
}

void	execute_one_cmd(t_minishell *minishell)
{
	char	**cmd;
	int		fd_in;
	int		fd_out;

	if (minishell->cmds->error_file == -1)
		exit(1);
	fd_in = 0;
	fd_out = 1;
	if (minishell->cmds->input_file)
		fd_in = open_file(minishell->cmds->input_file, 0, minishell->cmds->is_append);
	dup2(fd_in, STDIN_FILENO);
	if (minishell->cmds->output_file)
		fd_out = open_file(minishell->cmds->output_file, 1, minishell->cmds->is_append);
	dup2(fd_out, STDOUT_FILENO);
	cmd = fill_cmd_tab(minishell->cmds->args);
	// parse_and_check_cmd(minishell, cmd);
	if (cmd)
		execve(minishell->cmds->path_cmd, cmd, minishell->env);
}

int	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	return (0);
}

void	execute_builtin(t_cmds *cmd, t_minishell *minishell, int builtin_id)
{
	if (builtin_id == 1)
		pwd();
}

void	execute_cmd(t_cmds *current, t_minishell *minishell, int i)
{
	int	fd_in;
	int	fd_out;
	int	j;
	char	**cmd;
	int		builtin_id;

	if (current->error_file == -1)
		exit(1);
	fd_in = 0;
	fd_out = 1;
	if (current->input_file)
	{
		fd_in = open_file(current->input_file, 0, current->is_append);
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	else if (i > 0)
		dup2(minishell->pipes[i - 1][0], STDIN_FILENO);
	if (current->output_file)
	{
		fd_in = open_file(current->output_file, 1, current->is_append);
		dup2(fd_in, STDOUT_FILENO);
		close(fd_in);
	}
	else if (i < minishell->nb_cmd - 1)
		dup2(minishell->pipes[i][1], STDOUT_FILENO);
	j = 0;
	while (j < minishell->nb_cmd - 1)
	{
		close(minishell->pipes[j][0]);
		close(minishell->pipes[j][1]);
		j++;
	}
	builtin_id = is_builtin(current->args->arg);
	if (builtin_id)
	{
		execute_builtin(current, minishell, builtin_id);
		free(minishell->pid);
		free_pipes(minishell, minishell->pipes);
		free_all(minishell);
		exit(0);
	}
	cmd = fill_cmd_tab(current->args);
	parse_and_check_cmd(minishell, current, cmd);
	execve(current->path_cmd, cmd, minishell->env);
	perror("execve");
}

void	wait_child(t_minishell *minishell)
{
	int	i;
	int	status;

	i = 0;
	while (i < minishell->nb_cmd)
	{
		if (minishell->pid[i] > 0)
			waitpid(minishell->pid[i], &status, 0);
		if (WIFEXITED(status))
			error_code = WEXITSTATUS(status);
		i++;
	}
}

void	execute_all(t_minishell *minishell)
{
	int	status;
	int	i;

	i = 0;
	minishell->nb_cmd = count_cmd(minishell->cmds);
	minishell->pid = (pid_t *)malloc(sizeof(pid_t) * minishell->nb_cmd);

	t_cmds	*current_cmd;
	current_cmd = minishell->cmds;

	// if (minishell->nb_cmd > 1)
	// {
		init_pipes(minishell, minishell->nb_cmd);
		while (current_cmd)
		{
			// printf("YOLO\n");
			minishell->pid[i] = fork();
			if (minishell->pid[i] == 0)
				execute_cmd(current_cmd, minishell, i);
			i++;	
			current_cmd = current_cmd->next;
		}
		int j = 0;
		while (j < minishell->nb_cmd - 1)
		{
			close(minishell->pipes[j][0]);
			close(minishell->pipes[j][1]);
			j++;
		}
		wait_child(minishell);
		free_pipes(minishell, minishell->pipes);
	// }
	// else
	// {
	// 	if (minishell->cmds->args)
	// 	{
	// 		minishell->pid[0] = fork();
	// 		if (minishell->pid[0] == 0)
	// 			execute_one_cmd(minishell);
	// 		waitpid(minishell->pid[0], &status, 0);
	// 		if (WIFEXITED(status))
	// 			error_code = WEXITSTATUS(status);
	// 	}
	// }
	free(minishell->pid);
}
