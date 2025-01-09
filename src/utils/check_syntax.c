/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:34:12 by mosmont           #+#    #+#             */
/*   Updated: 2025/01/09 13:13:48 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	if_quote_close(char *line)
{
	int		i;
	int		in_quote;
	char	quote_char;

	i = 0;
	in_quote = 0;
	while (line[i])
	{
		if ((line[i] == '\'' || line[i] == '"') && in_quote == 0)
		{
			in_quote = 1;
			quote_char = line[i];
		}
		else if (line[i] == quote_char && in_quote == 1)
			in_quote = 0;
		i++;
	}
	if (in_quote == 0)
		return (FALSE);
	return (TRUE);
}

int	if_pipe_misplaced(char *line)
{
	int	start;
	int	end;

	start = 0;
	end = ft_strlen(line) - 1;
	while (line[start] && (line[start] == ' ' || line[start] == '\t'))
		start++;
	while (end > 0 && (line[end] == ' ' || line[end] == '\t'))
		end--;
	if (line[start] == '|' || line[end] == '|')
		return (TRUE);
	return (FALSE);
}

int	if_logical_operator(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (((line[i] == '|' && line[i + 1] == '|')
				|| (line[i] == '&' && line[i + 1] == '&'))
			&& !if_in_quote(line, &i))
			return (1);
		i++;
	}
	return (0);
}

int	if_wrong_redir(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (!if_in_quote(line, &i))
			if (line[i] == '<')
				if (line[i + 1] == '<')
					if (line[i + 2] == '<')
						return (TRUE);
		if (!if_in_quote(line, &i))
			if (line[i] == '>')
				if (line[i + 1] == '>')
					if (line[i + 2] == '>')
						return (TRUE);
		i++;
	}
	return (FALSE);
}

int	check_all_syntax(char *line)
{
	if (syntax_checker("Syntax error: quotation marks not closed\n", "",
			line, &if_quote_close) == TRUE)
		return (0);
	else if (syntax_checker("Syntax error: operator out of place\n", "",
			line, &if_pipe_misplaced) == TRUE)
		return (0);
	else if (syntax_checker("Syntax error: unsupported logic operator\n", "",
			line, &if_logical_operator) == TRUE)
		return (0);
	else if (syntax_checker("Syntax error: invalid redirection\n", "",
			line, &if_wrong_redir) == TRUE)
		return (0);
	else
		return (1);
}
