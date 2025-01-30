/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:46:15 by edetoh            #+#    #+#             */
/*   Updated: 2025/01/30 10:53:44 by edetoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	del_env(char *arg, char ***env)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	while ((*env)[i])
		i++;
	new_env = (char **)malloc(sizeof(char *) * i);
	i = 0;
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], arg, (ft_strlen(arg) + 0)) != 0)
		{
			new_env[j] = ft_strdup((*env)[i]);
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	free(*env);
	*env = new_env;
}

void	unset(t_args *args, char ***env)
{
	args = args->next;
	if (!args)
		return ;
	while (args)
	{
		del_env(args->arg, env);
		args = args->next;
	}
}
