/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 01:47:24 by jpceia            #+#    #+#             */
/*   Updated: 2021/12/03 10:37:26 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	*expand_operation(void *content)
{
	t_token *token;
	bool    check;

	token = (t_token *) content;
	if (token->type == TOKEN_DQUOTED || token->type == TOKEN_TEXT)
		check = true;
	else
		check = false;
	if (find_char(token->value, '$') && check == true)
	{
		token->value = ft_expander(token->value);
	}
	if (find_char(token->value, '~'))
		token->value = ft_expander_til(token);
	return (token);
}

char	**lex_and_expand(char *input)
{
	char			**arr;
	int				index;
	int				size;
	t_token			*token;
	t_token_list	*token_list;
	t_token_list	*token_it;

	token_list = lex(input);
	ft_lstmap(token_list, expand_operation, token_free);
	size = ft_lstsize(token_list);
	arr = (char **)malloc(sizeof(*arr) * (size + 1));
	if (!arr)
		return (NULL);
	index = 0;
	token_it = token_list;
	while (token_it)
	{
		token = token_it->content;
		if (is_word_token(token))
			arr[index++] = ft_strdup(token->value);
		token_it = token_it->next;
	}
	arr[index] = NULL;
	ft_lstclear(&token_list, token_free);
	return (arr);
}

t_command_tree	*parser(char *input)
{
	t_token_list	*token_list;
	t_token_list	*token_it;
	t_command_tree	*ast;

	if (!input)
		return (NULL);
	token_list = lex(input);
	// apply expander
	token_it = token_list;
	ast = command_tree_parse(&token_it, NULL);
	ft_lstclear(&token_list, token_free);
	return (ast);
}
