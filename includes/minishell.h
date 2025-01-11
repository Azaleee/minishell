/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:25:35 by mosmont           #+#    #+#             */
/*   Updated: 2025/01/10 18:52:06 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"

# include <stdio.h>
# include <stdlib.h>

# include <readline/readline.h>
# include <readline/history.h>

// LESS 	-> <
// GREAT	-> >
// DLESS	-> <<
// DGREAT	-> >>
// PIPE		-> |

# define TRUE 1
# define FALSE 0

// int	error_code;

typedef enum	e_token_type
{
	WORD,
	LESS,
	GREAT,
	DLESS,
	DGREAT,
	PIPE,
	DOLLAR,
	S_QUOTE,
	D_QUOTE,
	T_EOF
}				t_token_type;

typedef struct	s_lexer
{
	void				*value;
	t_token_type		token_type;
	struct s_lexer		*next;
}						t_lexer;

typedef struct	s_cmds
{
	char				**args;
	char				*input_file;
	char				*output_file;
	struct s_cmds		*next;
}						t_cmds;

typedef struct	minishell
{
	t_lexer				*input;
	t_cmds				*cmds;
}						t_minishell;

// LEXER PART

	// MAIN LEXER
void			tokenization(t_minishell *minishell, char *line);

	// LEXER LIST MANAGER
t_lexer			*new_token(char *content, t_token_type token);
void			add_back_token(t_lexer **lst, t_lexer *new);
void			token_clear(t_minishell *minishell);

	// LEXER UTILS
char			*get_operator(char *input, size_t *i);
int				is_operator(char c);
t_token_type	determine_operator(char *value);
char			if_in_quote(char *line, size_t *i);

// PARSER PART

void			clean_word_token(t_minishell *minishell, char **env);

t_cmds			*fill_cmds(t_lexer *tokens, t_cmds *cmds);

// UTILS
int				if_quote_close(char *line);
int				check_all_syntax(char *line);
char			if_in_quote(char *line, size_t *i);
void			remove_quote(char *line);
void			free_tab(char **tab);

	// PRINT ERROR
int				syntax_checker(char *msg_error, char *arg, char *line, int (*check)(char *));

// DEBUG FUNC
void			print_input(t_minishell *minishell);
void			display_tokens(t_lexer *tokens);

#endif