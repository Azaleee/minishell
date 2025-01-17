/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:25:14 by mosmont           #+#    #+#             */
/*   Updated: 2025/01/16 23:26:02 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// valgrind --leak-check=full --show-leak-kinds=all --suppressions=rl.txt --track-origins=yes ./minishell

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

char	**env_cpy(char **env)
{
	int	i;
	char **new_env;

	i = 0;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

t_minishell	*init_minishell(char **env)
{
	t_minishell	*minishell;

	minishell = malloc(sizeof(t_minishell));
	minishell->input = NULL;
	minishell->env = env_cpy(env);
	minishell->cmds = NULL;
	minishell->nb_cmd = 0;
	minishell->exit_code = 0;
	if (!minishell)
		exit(EXIT_FAILURE);
	return (minishell);
}

void	free_all(t_minishell *minishell)
{
	if (minishell->input)
		token_clear(minishell);
	if (minishell->cmds)
		cmds_clear(minishell);
	if (minishell->env)
		free_tab(minishell->env);
	if (minishell)
		free(minishell);
}

void	printf_all_cmd(t_cmds *cmds)
{
	t_args	*args;

	while (cmds)
	{
		args = cmds->args;
		printf("==================================\n");
		printf("New command : \n");
		while (args)
		{
			if (args)
				printf("%s\n", args->arg);
			args = args->next;
		}
		if (cmds->input_file)
			printf("\nInput file -> %s\n", cmds->input_file);
		
		if (cmds->output_file)
			printf("Output file -> %s\n", cmds->output_file);
		printf("Append yes or no hmm -> %d\n\n\n", cmds->is_append);
		cmds = cmds->next;
	}
}

int	error_code = 0;

int	main(int ac, char **av, char **env)
{
	char *line;
	t_minishell *minishell;

	line = NULL;
	minishell = init_minishell(env);
	// printf_env_var(minishell->env);

	// int i = 0;
	// while (env[i])
	// {
	// 	printf("%s\n", env[i]);
	// 	i++;
	// }

	// "\e[1;36m 😍💞💘 𝓶𝓲𝓷𝓲𝓼𝓱𝓮𝓵𝓵 💔💏💖>\e[0m "
	char *pwd;
	while (1)
	{
		pwd = malloc(ft_strlen("\e[1;32m➜\e[0m \e[1;36m") + ft_strlen(getenv("PWD")) + ft_strlen("$ \e[0m") + 1);
		ft_strlcpy(pwd, "\e[1;32m➜\e[0m \e[1;36m", ft_strlen("\e[1;32m➜ \e[0m\e[1;36m") + 1);
		ft_strlcat(pwd, getenv("PWD"), ft_strlen(pwd) + ft_strlen(getenv("PWD")) + 1);
		ft_strlcat(pwd, "$ \e[0m", ft_strlen(pwd) + ft_strlen("$ \e[0m") + 1);
		line = readline(pwd);
		if (!line)
		{
			write(1, "exit\n", 5);
			break ;
		}

		add_history(line);

		if (*line != '\0')
		{
			if (check_all_syntax(line))
			{
				tokenization(minishell, line);
				if (syntax_token_good(minishell->input))
				{
					clean_word_token(minishell, env);
					fill_struct_cmds(&minishell->cmds, minishell->input);
					// printf_all_cmd(minishell->cmds);
					execute_all(minishell);
					cmds_clear(minishell);
				}
				token_clear(minishell);
			}
		}
		free(pwd);
		free(line);
	}
	free(line);
	if (pwd)
		free(pwd);
	free_all(minishell);
}
