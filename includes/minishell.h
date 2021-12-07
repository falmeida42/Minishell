/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 21:09:35 by jpceia            #+#    #+#             */
/*   Updated: 2021/12/06 17:00:30 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <limits.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdbool.h>
#include "libft.h"
#include "map.h"

// btree where each node is t_ast_item
typedef t_btree	t_command_tree;

typedef struct	s_mini {
	t_command_tree	*tree;
	int				status;
	bool			exit;
	t_map			*env;
	char			*input;
	char			*parse_error;
}	t_mini;

t_mini	g_mini;

// Outfile

typedef	struct s_outfile
{
	char	*fname;
	bool	append;
}	t_outfile;

t_outfile		*outfile_new(char *fname, bool append);
void			outfile_free(void *ptr);

// Infile

typedef struct s_infile
{
	char	*data;
	bool	heredoc;
}	t_infile;

t_infile		*infile_new(char *str, bool heredoc);
void			infile_free(void *ptr);

// Commands

typedef struct s_simple_command
{
	t_list	*argv;
	t_list	*infiles;
	t_list	*outfiles;
}	t_simple_command;

void			simple_command_print(t_simple_command *cmd);
void			simple_command_free(void *ptr);
void			command_tree_free(void *ptr);

// Abstract Syntax Tree
// https://unix.stackexchange.com/questions/88850/precedence-of-the-shell-logical-operators
typedef enum e_ast_item_type
{
	AST_AND,
	AST_PIPE,
	AST_OR,
	AST_CMD,
	AST_PAREN
}	t_ast_item_type;

// command is NULL except when type == AST_CMD
typedef struct s_ast_item
{
	t_ast_item_type		type;
	t_simple_command	*cmd;
}	t_ast_item;

t_ast_item	*ast_item_new(t_ast_item_type type);
void		ast_item_free(void *ptr);
void		ast_item_print(void *ptr);

//free utility
void		mini_final_clear(t_mini *ptr);
void		mini_loop_clear(t_mini *ptr);

//commands.c
int			ft_pwd(char **argv, int fd);
int			ft_echo(char **argv, int fd);
int			ft_cd(char **argv, int fd);
int			ft_env(char **argv, int fd);
int			ft_export(char **argv, int fd);
int			ft_unset(char **argv, int fd);

int			ft_exec(char **argv);

bool		is_builtin(char *name);
int			builtin_execute(char **argv, int fd);
int			builtin_execute_parent(t_simple_command *cmd, bool do_fork, int fd);

void		get_signal(int signal);

// Redirects (for executor)
void		dup2_and_close(int new, int old);
// void		set_fd_out(t_outfile *out, int *fd);
void		set_fd_out_list(t_list *outfiles, int *fd);
void		set_fd_in_list(t_list *infiles, int *fd);

// Executor
int 		simple_command_execute_io(t_simple_command *cmd, bool fork_builtin, int fd_in, int fd_out);
int 		command_tree_execute_io(t_command_tree *tree, bool fork_builtin, int fd_in, int fd_out);
int 		command_tree_execute(t_command_tree *tree);
int 		pipe_execute_io(t_command_tree *left, t_command_tree *right, int fd_in, int fd_out);

// Utils
char	*lookup_full_path(char *path);
char	*normalize_path(char *path);
void	*clean_exit(void *ptr, char *err_msg, void (*free_fct)(void *));

// env variable
int			env_unset(char *key);
t_map		*env_set(char *key, char *value);
char		*env_get(char *key);


// Char Iterator

typedef char*	t_char_iterator;

char			char_iterator_peek(t_char_iterator *it);
char			char_iterator_next(t_char_iterator *it);

// Tokens

typedef enum e_token_type
{
	TOKEN_NULL,
	TOKEN_TEXT,
	TOKEN_QUOTED,
	TOKEN_DQUOTED,
	TOKEN_PIPE,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_GREATER,
	TOKEN_LESS,
	TOKEN_DGREATER,
	TOKEN_DLESS,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_BREKETS,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}	t_token;

typedef t_list	t_token_list;

typedef t_token_list* \
				t_token_iterator;

t_token			*token_new(t_token_type type, char *value);
void			token_free(void *ptr);
t_token			*token_iterator_next(t_token_iterator *it);
t_token			*token_iterator_peek(t_token_iterator *it);
bool			is_word_token(t_token *token);
bool			is_redirection_token(t_token *token);
bool			is_simple_command_token(t_token *token);
bool			is_empty_word_token(t_token *token);

char			*syntax_error_msg(t_token *token);

t_btree			*ast_node_from_token(t_token *token);

// Lookup functions
t_token			*token_list_lookup_logical(t_token_list *lst, t_token *end_token);
t_token			*token_list_lookup_pipe(t_token_list *lst, t_token *end_token);

// Lexer functions (Aka tokenizer)
t_token_list	*lex(char *input);

t_token			*take_twochar_symbol(t_char_iterator *cursor);
t_token			*take_symbol(t_char_iterator *cursor);
t_token			*take_dquoted(char **cursor);
t_token			*take_quoted(char **cursor);
t_token			*take_breakets(char **cursor);
t_token			*take_text(char **cursor);

// Parsing
t_simple_command\
				*simple_command_parse(t_token_iterator *it);
t_command_tree	*command_tree_parse(t_token_iterator *it, t_token *end_token);

t_command_tree	*parser(char *input);

char			**lex_and_expand(char *input);

// Expander
char			*ft_expander(char *str);

// Expander Til
char	*ft_expander_til(t_token *token);

//Expander breakets
char	*ft_expand_brekets(char *str);
char    *cmp_brekets(char *str);
#endif
