/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 18:29:58 by jpceia            #+#    #+#             */
/*   Updated: 2021/12/08 08:51:55 by jpceia           ###   ########.fr       */
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
	if ((token->type == TOKEN_DQUOTED || token->type == TOKEN_TEXT)
		&& ft_contains('$', token->value))
		token->value = ft_expander(token->value);
	if (!token->value)
		return (NULL);
	if (token->type == TOKEN_TEXT && *token->value == '~')
		token->value = ft_expander_til(token);
	return (token);
}

char	*ft_expander(char *str)
{
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == '?')
				return (ft_expander(replace_dollar_status(str, i)));
			else if (str[i + 1] == '{')
				return (ft_expander(replace_dollar_brackets(str, i)));
			else if (!(ft_contains(str[i + 1], " \"") || str[i + 1] == '\0'))
				return (ft_expander(replace_dollar_generic(str, i)));
		}
		i++;
	}
	return (str);
}
