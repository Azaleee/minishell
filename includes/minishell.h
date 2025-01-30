/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+         +:+     */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:25:35 by mosmont           #+#    #+#             */
/*   Updated: 2025/01/20 12:52:25 by edetoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/**************************
 **      INCLUDES       **
 **************************/

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <signal.h>
# include <bits/sigaction.h>
# include <asm-generic/signal-defs.h>

/**************************
 **     DEFINITIONS     **
 **************************/

// Token types for parsing
# define TRUE 1
# define FALSE 0

// Operators
// # define LESS    "<"
// # define GREAT   ">"
// # define DLESS   "<<"
// # define DGREAT  ">>"
// # define PIPE    "|"

/**************************
 **     GLOBAL VARS     **
 **************************/

extern int	g_error_code;

/**************************
 **       ENUMS         **
 **************************/

typedef enum e_token_type
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
}	t_tok_t;

/**************************
 **      STRUCTURES     **
 **************************/

typedef struct s_lexer
{
	void			*value;
	t_tok_t			token_type;
	struct s_lexer	*next;
}					t_lexer;

typedef struct s_args
{
	char			*arg;
	struct s_args	*next;
}					t_args;

typedef struct s_cmds
{
	t_args			*args;
	char			*input_file;
	char			*output_file;
	char			*path_cmd;
	int				is_append;
	int				error_file;
	struct s_cmds	*next;
}					t_cmds;

typedef struct s_minishell
{
	t_lexer			*input;
	t_cmds			*cmds;
	char			**env;
	int				**pipes;
	pid_t			*pid;
	int				nb_cmd;
	int				exit_code;
	int				*heredoc_counter;
	char			*pwd;
}					t_minishell;

/**************************
 **    FUNCTION PROTOS  **
 **************************/

/**
 * Signal Handler
 */
void	init_signals(void);
void	handle_sigquit(int signal);
void	handle_sigint_cmd(int signal);
void	handle_sigint_heredoc(int sig);

/**
 * Built-in Functions
 */
int		pwd(void);
void	print_env(char **env);
int		cd(t_args *args, char ***env);
void	unset(t_args *args, char ***env);
int		ft_exit(t_minishell *minishell, int nb_commands);
void	echo(t_args *args, char **env);

// ------ Export ------
int		ft_export(t_args *args, char ***env);

int		is_valid_identifier(char *str);
void	print_export_error(char *arg);
void	sort_env(char **env);
void	print_sorted_env(char **env);
// ------ end export ------

/**
 * Execution Handlers
 */
void	execute_all(t_minishell *minishell);

void	bultins_exe(int builtin_in_parent, int builtin_id, t_cmds *current, t_minishell *minishell);

/**
 * Built-ins Manager
 */
int		is_builtin_parent(char *cmd);
int		is_builtin_child(char *cmd);
void	execute_builtin_child(t_cmds *cmd, t_minishell *minishell, int builtin_id);
int		execute_builtin_parent(t_cmds *cmd, t_minishell *minishell);


/**
 * Pipes Management
 */
void	init_pipes(t_minishell *minishell, int nb_cmd);
void	free_pipes(t_minishell *minishell, int **tab);
void	close_all_pipes(t_minishell *minishell);
void	close_unused_pipes(t_minishell *minishell, int i);

/**
 * Command Management
 */
char	*get_path_cmd(char *cmd, char *path);
char	**fill_cmd_tab(t_args *args);
void	check_access_cmd(t_minishell *minishell, char *path_cmd);
void	parse_and_check_cmd(t_minishell *minishell, t_cmds *current,
			char **cmd);

/**
 * Redirections
 */
int		open_file(char *file, int mode, int append_mode);
void	set_input_redir(t_cmds *current, t_minishell *minishell, int i);
void	set_output_redir(t_cmds *current, t_minishell *minishell, int i);

/**
 * Parser
 */
int		open_heredoc(char *input_file);
void	read_heredoc(char *eof, char *input_file);
void	get_heredoc_redir(t_minishell *minishell, t_cmds *cmds, t_lexer **token);
void	get_input_redir(t_cmds *cmds, t_lexer **token);
void	get_output_redir(t_cmds *cmds, t_lexer **token);
void	get_output_append_redir(t_cmds *cmds, t_lexer **token);
char	*create_temp_file(int *heredoc_counter);

/**
 * Environment Variable Expansion
 */
char	*get_env_var(char *value, size_t *start);
char	*expand_env_var(char *value, char **env, size_t i);
char	*replace_actual(char *value, char *env_value, char *env_var,
			size_t start);
int		check_syntax_env_var(int c);

/**
 * Token Cleaning
 */
void	clean_word_token(t_minishell *minishell, char **env);

/**
 * Command Structure Filling
 */
void	fill_struct_cmds(t_minishell *minishell, t_cmds **cmds, t_lexer *token);

/**
 * Utility Functions
 */
void	*get_next_cmd(void *node);
void	*get_next_args(void *node);
void	*get_next_token(void *node);
void	set_next_cmd(void *node, void *next);
void	set_next_args(void *node, void *next);
void	set_next_token(void *node, void *next);
void	lst_add_back(void **lst, void *new_node, void *(*get_next)(void *),
			void (*set_next)(void *, void *));
t_cmds	*init_cmd(void);
t_args	*init_arg(char *value);
t_lexer	*new_token(char *content, t_tok_t token);
void	args_clear(t_args **args);
void	cmds_clear(t_cmds **cmds);
void	token_clear(t_minishell *minishell);
char	**set_env_value(char *env_var, char *env_value, char ***env);
char	*get_env_value(char *env_var, char **env);
char	**env_cpy(char **env);
void	free_tab(char **tab);
void	free_all(t_minishell *minishell);
void	exit_and_free(t_minishell *minishell, int exit_code);
int		syntax_checker(char *msg_error, char *arg, char *line,
			int (*check)(char *));
int		print_error(char *message, char *cmd, int exit_code,
			t_minishell *minishell);
int		check_all_syntax(char *line);
int		syntax_token_good(t_lexer *token);
char	if_in_quote(char *line, size_t *i);
void	remove_quote(char *line);
int		if_quote_close(char *line);

/**
 * Lexer
 */
void	tokenization(t_minishell *minishell, char *line);
int		is_operator(char c);
char	*get_operator(char *input, size_t *i);
t_tok_t	determine_operator(char *value);
char	*parse_word(char *line, size_t *i);

/**
 * Debug Functions
 */
void	display_tokens(t_lexer *tokens);
void	printf_all_cmd(t_cmds *cmds);

#endif
