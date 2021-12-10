/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 18:29:58 by jpceia            #+#    #+#             */
/*   Updated: 2021/12/10 22:55:47 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

void	*expand_operation(void *content)
{
	t_token	*token;

	token = (t_token *) content;
	if (!token || !is_word_token(token) || !token->value)
		return (token);
	if (*token->value == '~')
		token->value = ft_expander_til(token);
	token->value = ft_expander(token->value);
	if (!token->value)
		return (NULL);
	token->value = clean_string(token->value);
	return (token);
}

char	*ft_expander(char *str)
{
	char	c;
	char	*pos;

	if (!str)
		return (NULL);
	pos = ft_strchr_unquoted(str, '$');
	if (!pos)
		return (str);
	c = *(pos + 1);
	if (c == '?')
		return (ft_expander(replace_dollar_status(str, pos - str)));
	if (c == '{')
		return (ft_expander(replace_dollar_brackets(str, pos - str)));
	if (!(ft_contains(c, " \"") || c == '\0'))
		return (ft_expander(replace_dollar_generic(str, pos - str)));
	return (str);
}