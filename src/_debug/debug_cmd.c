/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:11:19 by mosmont           #+#    #+#             */
/*   Updated: 2025/01/17 19:23:19 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
