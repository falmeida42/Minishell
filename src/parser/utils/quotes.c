/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 23:34:24 by jpceia            #+#    #+#             */
/*   Updated: 2021/12/10 23:34:41 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_contains_unquoted(char *str, char needle)
{
	int				i;
	char			prev_char;
	t_quote_type	quote_type;

	i = 0;
	prev_char = 0;
	quote_type = QUOTE_NONE;
	while (str[i])
	{
		quote_type = update_quote_type(quote_type, str[i], prev_char);
		if (quote_type != QUOTE_SINGLE && str[i] == needle
			&& prev_char != '\\')
			return (true);
		prev_char = update_prev_char(str[i], prev_char);
		i++;
	}
	return (false);
}

char	*ft_strchr_unquoted(char *str, char needle)
{
	int				i;
	char			prev_char;
	t_quote_type	quote_type;

	i = 0;
	prev_char = 0;
	quote_type = QUOTE_NONE;
	while (str[i])
	{
		quote_type = update_quote_type(quote_type, str[i], prev_char);
		if (quote_type != QUOTE_SINGLE && str[i] == needle
			&& prev_char != '\\')
			return (&str[i]);
		prev_char = update_prev_char(str[i], prev_char);
		i++;
	}
	return (NULL);
}
