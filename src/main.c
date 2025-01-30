/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:25:14 by mosmont           #+#    #+#             */
/*   Updated: 2025/01/30 11:36:58 by edetoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_error_code = 0;

t_minishell	*init_minishell(char **env)
{
	t_minishell	*minishell;

	minishell = malloc(sizeof(t_minishell));
	minishell->input = NULL;
	minishell->env = env_cpy(env);
	minishell->cmds = NULL;
	minishell->nb_cmd = 0;
	minishell->exit_code = 0;
	minishell->heredoc_counter = malloc(sizeof(int));
	*minishell->heredoc_counter = 0;
	minishell->nb_cmd = 0;
	minishell->pipes = NULL;
	minishell->pid = NULL;
	minishell->pwd = NULL;
	if (!minishell)
		exit(EXIT_FAILURE);
	return (minishell);
}

char	*pwd_print_readline(char **env)
{
	char	*pwd;
	char	*temp;

	temp = get_env_value("PWD", env);
	if (!temp)
	{
		free(temp);
		return (ft_strdup("\e[1;32m➜\e[0m \e[1;36m$ \e[0m"));
	}
	free(temp);
	temp = get_env_value("PWD", env);
	pwd = malloc(ft_strlen("\e[1;32m➜\e[0m \e[1;36m") \
	+ ft_strlen(temp)
			+ ft_strlen("$ \e[0m") + 1);
	ft_strlcpy(pwd, "\e[1;32m➜\e[0m \e[1;36m",
		ft_strlen("\e[1;32m➜ \e[0m\e[1;36m") + 1);
	free(temp);
	temp = get_env_value("PWD", env);
	ft_strlcat(pwd, temp, ft_strlen(pwd) \
	+ ft_strlen(temp)
		+ 1);
	ft_strlcat(pwd, "$ \e[0m", ft_strlen(pwd) + ft_strlen("$ \e[0m") + 1);
	return (free(temp), pwd);
}

// printf_all_cmd(minishell->cmds);
void	shell_loop(t_minishell *minishell, char *line)
{
	if (*line != '\0')
	{
		if (check_all_syntax(line) == 0)
		{
			tokenization(minishell, line);
			// g_error_code = syntax_token_good(minishell->input);
			if (syntax_token_good(minishell->input))
			{
				clean_word_token(minishell, minishell->env);
				// display_tokens(minishell->input); // debug
				fill_struct_cmds(minishell, &minishell->cmds, minishell->input);
				if (minishell->cmds->args)
					execute_all(minishell);
				cmds_clear(&minishell->cmds);
			}
			token_clear(minishell);
		}
	}
	free(line);
}

int	main(int ac, char **av, char **env)
{
	char		*line;
	t_minishell	*minishell;

	line = NULL;
	(void)ac;
	(void)av;
	minishell = init_minishell(env);
	init_signals();
	while (1)
	{
		minishell->pwd = pwd_print_readline(minishell->env);
		line = readline(minishell->pwd);
		if (!line)
		{
			write(1, "exit\n", 5);
			break ;
		}
		add_history(line);
		shell_loop(minishell, line);
		// printf("g_error_code = %d\n", g_error_code); // debug
		free(minishell->pwd);
	}
	free(line);
	free_all(minishell);
}
// valgrind --leak-check=full --show-leak-kinds=all --suppressions=rl.txt
// --track-origins=yes ./minishell

// void	printf_env_var(t_env *env)
// {
// 	while (env)
// 	{
// 		printf("%s=", env->env_name);
// 		printf("%s\n", env->env_value);
// 		env = env->next;
// 	}
// }

// void	*get_next_env(void *node)
// {
// 	return ((t_env *)node)->next;
// }

// void	set_next_env(void *node, void *next)
// {
// 	((t_env *)node)->next = (t_env *)next;
// }

// t_env	*init_env(void)
// {
// 	t_env	*env;

// 	env = malloc(sizeof(t_env));
// 	env->env_name = NULL;
// 	env->env_value = NULL;
// 	env->next = NULL;
// 	return (env);
// }

// void	init_all_env(t_env **env_struct, char **env)
// {
// 	int		size_env;
// 	t_env	*current;
// 	int		i;
// 	int		j;

// 	size_env = 0;
// 	current = init_env();
// 	while (env[size_env])
// 	{
// 		i = 0;
// 		while (env[size_env][i] != '=')
// 			i++;
// 		if (i > 0)
// 			current->env_name = ft_substr(env[size_env], 0, (size_t)i);
// 		j = i;
// 		while (env[size_env][j])
// 			j++;
// 		current->env_value = ft_substr(env[size_env], i + 1, j);
// 		lst_add_back((void **)env_struct, current, get_next_env, set_next_env);
// 		current = init_env();
// 		size_env++;
// 	}
// }
