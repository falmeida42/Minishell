/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 17:52:49 by jpceia            #+#    #+#             */
/*   Updated: 2021/12/06 15:36:37 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

t_token	*take_twochar_symbol(t_char_iterator *cursor)
{
	t_token	*token;

	if (!ft_strncmp(*cursor, "||", 2))
		token = token_new(TOKEN_OR, ft_strdup("||"));
	else if (!ft_strncmp(*cursor, "&&", 2))
		token = token_new(TOKEN_AND, ft_strdup("&&"));
	else if (!ft_strncmp(*cursor, ">>", 2))
		token = token_new(TOKEN_DGREATER, ft_strdup(">>"));
	else if (!ft_strncmp(*cursor, "<<", 2))
		token = token_new(TOKEN_DLESS, ft_strdup("<<"));
	else
		return (NULL);
	char_iterator_next(cursor);
	char_iterator_next(cursor);
	return (token);
}

t_token	*take_symbol(t_char_iterator *cursor)
{
	t_token			*token;
	char			c;

	token = take_twochar_symbol(cursor);
	if (token)
		return (token);
	c = char_iterator_peek(cursor);
	if (c == '|')
		token = token_new(TOKEN_PIPE, ft_strdup("|"));
	else if (c == '>')
		token = token_new(TOKEN_GREATER, ft_strdup(">"));
	else if (c == '<')
		token = token_new(TOKEN_DLESS, ft_strdup("<"));
	else if (c == '(')
		token = token_new(TOKEN_LPAREN, ft_strdup("("));
	else if (c == ')')
		token = token_new(TOKEN_RPAREN, ft_strdup(")"));
	else
		token = NULL;
	char_iterator_next(cursor);
	return (token);
}

int		cont_quotes(char *str)
{
	int	i;
	int	len;
	
	len = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (i > 0 && str[i] == '"' && str[i - 1] != '\\')
			len++;
		i++;
	}
	return (len);
}

char	*remove_quotes(char *str)
{
	char *str2;
	int	len;
	int i;
	int	j;
	len = ft_strlen(str);
	str2 = malloc(sizeof(char) * len - cont_quotes(str));

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		while (str[i] == '"')
		{
			if (i > 0 && str[i - 1] == '\\')
			{
				str2[j] = str[i];
				i++;
				j++;
			}
			i++;
		}
		str2[j] = str[i];

		i++;
		j++;
	}
	str2[j] = '\0';
	return (str2);
}

t_token	*take_dquoted(char **cursor)
{
	char	c;
	char	prev_char;
	char	*start;
	char	*end;
	int		len;

	start = *cursor;
	if (ft_contains('{', start))
		ft_expand_brekets(start);
	char_iterator_next(cursor);
	c = char_iterator_peek(cursor);
	len = 1;
	prev_char = 0;
	end = NULL;
	while (c)
	{
		if (c == '"' && prev_char != '\\')
			len++;
		if (len % 2 == 0)
		{
			if (*(*cursor + 1) == ' ')
			{
				end = *cursor;
				char_iterator_next(cursor);
				break;
			}
		}
		prev_char = c;
		c = char_iterator_next(cursor);
	}
	start = ft_substr(start, 0, end - (start - 1));
	return (token_new(TOKEN_DQUOTED, remove_quotes(start)));
}

int	ft_contains_breakets(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
			return (1);
		if (str[i] == '{')
		{
			while (str[i] != '\0')
			{
				if (str[i] == '}')
					return (0);
				i++;
			}
			return (1);
		}
		i++;
	}
	return (1);
}

t_token	*take_breakets(char **cursor)
{
	char	c;
	char	*start;
	char	*end;

	start = *cursor;
	if (ft_contains_breakets(start))
		return (take_text(cursor));
	c = char_iterator_peek(cursor);
	while (c)
	{
		if (c == '}')
			break ;
		c = char_iterator_next(cursor);
	}
	end = *cursor;
	char_iterator_next(cursor);
	return (token_new(TOKEN_BREKETS, ft_substr(start, 0, end - (start - 1))));
}

t_token	*take_quoted(char **cursor)
{
	char	c;
	char	prev_char;
	char	*start;
	char	*end;

	char_iterator_next(cursor);
	start = *cursor;
	prev_char = 0;
	c = char_iterator_peek(cursor);
	while (c && (c != '\'' || prev_char == '\\'))
	{
		prev_char = c;
		c = char_iterator_next(cursor);
	}
	end = *cursor;
	char_iterator_next(cursor);
	return (token_new(TOKEN_QUOTED, ft_substr(start, 0, end - start)));
}

t_token	*take_text(char **cursor)
{
	char	c;
	char	*start;
	char	*end;

	start = *cursor;
	c = char_iterator_peek(cursor);
	while (c && !ft_contains(c, " |&><)("))
		c = char_iterator_next(cursor);
	end = *cursor;
	return (token_new(TOKEN_TEXT, ft_substr(start, 0, end - start)));
}
