/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 18:29:58 by jpceia            #+#    #+#             */
/*   Updated: 2021/12/07 19:38:12 by jpceia           ###   ########.fr       */
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

int	needs_to_replace_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$'
			&& !(ft_contains(str[i + 1], " \t") || str[i + 1] == '\0'))
			return (1);
		i++;
	}
	return (0);
}

char	*ft_expander(char *str)
{
	char	*result;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	result = str;
	if (!needs_to_replace_dollar(str))
		return (str);
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == '?')
				result = replace_dollar_status(str, i);
			else if (str[i + 1] == '{')
				result = replace_dollar_brackets(str, i);
			else if (ft_contains(str[i + 1], " \"") || str[i + 1] == '\0')
			{
				i++ ;
				continue ;
			}
			else
				result = replace_dollar_generic(str, i);
			break ;
		}
		i++;
	}
	return (ft_expander(result));
}
