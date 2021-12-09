/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 17:52:49 by jpceia            #+#    #+#             */
/*   Updated: 2021/12/09 16:49:44 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

char	*remove_quotes(char *str)
{
	char	*str2;
	int		i;
	int		j;

	str2 = malloc(ft_strlen(str) + 1);
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
	free(str);
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
				break ;
			}
		}
		prev_char = c;
		c = char_iterator_next(cursor);
	}
	start = ft_substr(start, 0, end - (start - 1));
	return (token_new(TOKEN_DQUOTED, remove_quotes(start)));
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
	return (token_new(TOKEN_TEXT, remove_quotes(ft_substr(start, 0, end - start))));
}
