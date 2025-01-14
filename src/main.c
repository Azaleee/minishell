/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:25:14 by mosmont           #+#    #+#             */
/*   Updated: 2025/01/14 20:50:40 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// valgrind --leak-check=full --show-leak-kinds=all --suppressions=rl.txt --track-origins=yes ./minishell

t_minishell	*init_minishell(char **env)
{
	t_minishell	*minishell;

	minishell = malloc(sizeof(t_minishell));
	minishell->input = NULL;
	minishell->env = env;
	minishell->cmds = NULL;
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
		printf("\nInput file -> %s\n", cmds->input_file);
		printf("Output file -> %s\n", cmds->output_file);
		printf("Append yes or no hmm -> %d\n", cmds->is_append);
		cmds = cmds->next;
	}
}

int	main(int ac, char **av, char **env)
{
	char *line;
	t_minishell *minishell;
	// int	error_code;

	line = NULL;
	minishell = init_minishell(env);
	// error_code = 0;

	// int i = 0;
	// while (env[i])
	// {
	// 	printf("%s\n", env[i]);
	// 	i++;
	// }

	while (1)
	{
		line = readline("\e[1;36m 😍💞💘 𝓶𝓲𝓷𝓲𝓼𝓱𝓮𝓵𝓵 💔💏💖>\e[0m ");
		if (!line)
		{
			write(1, "exit\n", 5);
			break ;
		}

		add_history(line);

		if (check_all_syntax(line))
		{
			tokenization(minishell, line);
			if (syntax_token_good(minishell->input))
			{
				clean_word_token(minishell, env);
				fill_struct_cmds(&minishell->cmds, minishell->input);
				printf_all_cmd(minishell->cmds);
			}
			token_clear(minishell);
			cmds_clear(minishell);
		}
		free(line);
	}
	free(line);
	free_all(minishell);
}
