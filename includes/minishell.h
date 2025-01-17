/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:25:35 by mosmont           #+#    #+#             */
/*   Updated: 2025/01/16 22:47:53 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"

# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/wait.h>

# include <readline/readline.h>
# include <readline/history.h>

// LESS 	-> <
// GREAT	-> >
// DLESS	-> <<
// DGREAT	-> >>
// PIPE		-> |

# define TRUE 1
# define FALSE 0

extern int	error_code;

typedef enum	e_token_type
{
	WORD,
	LESS,
	GREAT,
	DGREAT,
	DLESS,
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

typedef struct 	s_args
{
	char				*arg;
	struct s_args		*next;
}						t_args;

typedef struct	s_cmds
{
	t_args				*args;
	char				*input_file;
	char				*output_file;
	char				*path_cmd;
	int					is_append;
	int					error_file;
	struct s_cmds		*next;
}						t_cmds;

typedef struct	s_env
{
	char				*env_name;
	char				*env_value;
	struct s_env		*next;
}						t_env;

typedef struct	s_minishell
{
	t_lexer				*input;
	t_cmds				*cmds;
	char				**env;
	int					**pipes;
	pid_t				*pid;
	int					nb_cmd;
	int					exit_code;
}						t_minishell;


int	pwd(void);

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

// PARSER PART

void			clean_word_token(t_minishell *minishell, char **env);

void			fill_struct_cmds(t_cmds **cmds, t_lexer *token);
void			cmds_clear(t_minishell *minishell);

// UTILS
int				if_quote_close(char *line);
int				check_all_syntax(char *line);
int				syntax_token_good(t_lexer *token);
char			if_in_quote(char *line, size_t *i);
void			remove_quote(char *line);
void			free_tab(char **tab);
void			free_all(t_minishell *minishell);

void			execute_all(t_minishell *minishell);

// LIST MANAGER
void			lst_add_back(void **lst, void *new_node, void *(*get_next)(void *),
					void (*set_next)(void *, void *));
void			set_next_token(void *node, void *next);
void			*get_next_token(void *node);

	// PRINT ERROR
int				syntax_checker(char *msg_error, char *arg, char *line, int (*check)(char *));

// DEBUG FUNC
void			print_input(t_minishell *minishell);
void			display_tokens(t_lexer *tokens);

#endif