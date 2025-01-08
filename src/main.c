/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:25:14 by mosmont           #+#    #+#             */
/*   Updated: 2025/01/08 17:10:51 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// valgrind --leak-check=full --show-leak-kinds=all --suppressions=rl.txt --track-origins=yes ./minishell

t_minishell	*init_minishell()
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

int	main(void)
{
	char *line;
	t_minishell	*minishell;

	line = NULL;
	minishell = init_minishell();
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			write(1, "exit\n", 5);
			break ;
		}

		if (check_all_syntax(line))
		{
			tokenization(minishell, line);
			token_clear(minishell);
		}
		
		free(line);
	}
	free(line);
	free_all(minishell);
}