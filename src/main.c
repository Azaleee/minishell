/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:25:14 by mosmont           #+#    #+#             */
/*   Updated: 2025/01/09 20:22:08 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// valgrind --leak-check=full --show-leak-kinds=all --suppressions=rl.txt --track-origins=yes ./minishell

t_minishell	*init_minishell(void)
{
	t_minishell	*minishell;

	minishell = malloc(sizeof(t_minishell));
	if (!minishell)
		exit(EXIT_FAILURE);
	return (minishell);
}

void	free_all(t_minishell *minishell)
{
	if (minishell)
		free(minishell);
	// if (minishell->input)
	// 	token_clear(minishell);
}

int	main(int ac, char **av, char **env)
{
	char *line;
	t_minishell *minishell;
	// int	error_code;

	line = NULL;
	minishell = init_minishell();
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
			clean_word_token(minishell, env);
			token_clear(minishell);
		}

		free(line);
	}
	free(line);
	free_all(minishell);
}