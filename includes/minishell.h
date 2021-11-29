/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 21:09:35 by jpceia            #+#    #+#             */
/*   Updated: 2021/11/29 11:15:26 by jceia            ###   ########.fr       */
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

typedef struct	s_mini {
	int		status;
	bool	exit;
	t_map	*env;
} t_mini;

t_mini	g_mini;

// Commands

typedef struct s_simple_command
{
	t_list	*argv;
	char	*infile;
	char	*outfile;
	bool	here_doc;
	bool	append;
}	t_simple_command;

typedef t_list	t_piped_command;

void			simple_command_print(t_simple_command *cmd);
void			piped_command_print(t_piped_command *command);
void			simple_command_free(void *ptr);
void			piped_command_free(void *ptr);
void			commands_group_free(void *ptr);

// Abstract Syntax Tree
// https://unix.stackexchange.com/questions/88850/precedence-of-the-shell-logical-operators
typedef enum e_ast_node_type
{
	AST_AND,
	AST_OR,
	AST_CMD,
}	t_ast_node_type;

// command is NULL except when type == AST_CMD
typedef struct s_ast_node
{
	t_ast_node_type	type;
	t_piped_command	*command;
}	t_ast_node;

t_ast_node	*ast_node_new(t_ast_node_type type);
void		ast_node_free(void *ptr);

// btree where each node is t_ast_node
typedef t_btree	t_commands_group;

//free utility
void		free_struct(void);

//commands.c
int			ft_pwd(char **argv);
int			ft_echo(char **argv);
int			ft_cd(char **argv);
int			ft_env(char **argv);
int			ft_export(char **argv);
int			ft_unset(char **argv);

int			ft_exec(char **argv);

bool	is_builtin(char *name);
int	builtin_execute(char **argv);

void		get_signal(int signal);

// Utils
char	*lookup_full_path(char *path);
char	*normalize_path(char *path);

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
bool			is_word_token(t_token *token);
bool			is_redirection_token(t_token *token);
bool			is_simple_command_token(t_token *token);

// Lexer functions (Aka tokenizer)
t_token_list	*lex(char *input);

t_token			*take_twochar_symbol(t_char_iterator *cursor);
t_token			*take_symbol(t_char_iterator *cursor);
t_token			*take_dquoted(char **cursor);
t_token			*take_quoted(char **cursor);
t_token			*take_text(char **cursor);

// Parsing
t_simple_command\
				*simple_command_parse(t_token_iterator *it);
t_piped_command	*piped_command_parse(t_token_iterator *it);
t_commands_group\
				*commands_group_parse(t_token_iterator *it);

t_commands_group	*parser(char *input);
char				**lex_and_expand(char *input);

// Expander
char	*ft_expander(char *str);

#endif
