/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 03:36:52 by jpceia            #+#    #+#             */
/*   Updated: 2021/11/14 06:34:05 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef char* char_iterator;

char char_iterator_peek(char_iterator *it);
char char_iterator_next(char_iterator *it);

typedef enum e_token_type
{
    TOKEN_NULL,
    TOKEN_TEXT,         // text
    TOKEN_QUOTED_TEXT,  // 'text'
    TOKEN_DQUOTED_TEXT, // "text"
    TOKEN_SEMICOLON,    // ;
    TOKEN_PIPE,         // |
    TOKEN_AMPERSAND,    // &
    TOKEN_AND,          // &&
    TOKEN_OR,           // ||
    TOKEN_GREATER,      // >
    TOKEN_LESS,         // <
    TOKEN_DGREATER,     // >>
    TOKEN_DLESS,        // <<
    TOKEN_LEFT_PAREN,   // (
    TOKEN_RIGHT_PAREN,  // )
}   t_token_type;

typedef struct s_token
{
    t_token_type    type;
    char            *value;
}   t_token;

typedef struct s_token_list t_token_list;

typedef struct s_token_list
{
    t_token         *token;
    t_token_list    *next;
}   t_token_list;

// tokenizer
t_token *token_new(t_token_type type, char *value);
void token_free(t_token *token);
t_token_list *token_list_new(t_token *token);
void token_list_free(t_token_list *list);
t_token_list *token_list_pushback(t_token_list **list, t_token *token);
int token_list_size(t_token_list *list);

// lexer_utils
t_token *take_twochar_symbol(char_iterator *cursor);
t_token *take_symbol(char_iterator *cursor);
t_token *take_dquoted(char **cursor);
t_token *take_quoted(char **cursor);
t_token *take_text(char **cursor);

#endif
