/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 01:47:24 by jpceia            #+#    #+#             */
/*   Updated: 2021/12/11 14:35:29 by jceia            ###   ########.fr       */
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
	token_it = token_list;
	ast = command_tree_parse(&token_it, NULL);
	ft_lstclear(&token_list, token_free);
	return (ast);
}
