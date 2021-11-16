/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   parser.h										   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: jpceia <joao.p.ceia@gmail.com>			 +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2021/11/14 03:36:52 by jpceia			#+#	#+#			 */
/*   Updated: 2021/11/14 17:45:19 by jpceia		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"
# include <stdbool.h>

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
bool			is_simple_cmd_token(t_token *token);

// Lexer functions (Aka tokenizer)
t_token_list	*lex(char *input);

t_token			*take_twochar_symbol(t_char_iterator *cursor);
t_token			*take_symbol(t_char_iterator *cursor);
t_token			*take_dquoted(char **cursor);
t_token			*take_quoted(char **cursor);
t_token			*take_text(char **cursor);

#endif
