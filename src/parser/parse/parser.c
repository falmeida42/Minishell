/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 01:47:24 by jpceia            #+#    #+#             */
/*   Updated: 2021/12/07 18:25:04 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_empty_word_token_wrap(void *ptr)
{
	return (is_empty_word_token((t_token *)ptr));
}

t_command_tree	*parser(char *input)
{
	t_token_list	*token_list;
	t_token_list	*token_it;
	t_command_tree	*ast;

	if (!input)
		return (NULL);
	token_list = lex(input);
	apply_star_expander(token_list);
	ft_lstapplymap(token_list, expand_operation);
	ft_lstremove_if(&token_list, is_empty_word_token_wrap, token_free);
	token_it = token_list;
	ast = command_tree_parse(&token_it, NULL);
	ft_lstclear(&token_list, token_free);
	return (ast);
}
