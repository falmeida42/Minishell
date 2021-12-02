/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lookup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 09:09:33 by jpceia            #+#    #+#             */
/*   Updated: 2021/12/02 09:10:31 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_token	*token_list_lookup_logical(t_token_list *lst, t_token *end_token)
{
	int		parent_count;
	t_token	*token;

	parent_count = 0;
	while (lst)
	{
		token = (t_token *)lst->content;
		if (token == end_token)
			return (NULL);
		if (token->type == TOKEN_LPAREN)
			parent_count++;
		else if (token->type == TOKEN_RPAREN)
			parent_count--;
		else if ((token->type == TOKEN_AND || token->type == TOKEN_OR)
			&& parent_count == 0)
			return (token);
		lst = lst->next;
	}
	return (NULL);
}

t_token	*token_list_lookup_pipe(t_token_list *lst, t_token *end_token)
{
	int		parent_count;
	t_token	*token;

	parent_count = 0;
	while (lst)
	{
		token = (t_token *)lst->content;
		if (token == end_token)
			return (NULL);
		if (token->type == TOKEN_LPAREN)
			parent_count++;
		else if (token->type == TOKEN_RPAREN)
			parent_count--;
		else if (token->type == TOKEN_PIPE && parent_count == 0)
			return (token);
		lst = lst->next;
	}
	return (NULL);
}
