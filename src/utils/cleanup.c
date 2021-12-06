/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 17:32:09 by fferreir          #+#    #+#             */
/*   Updated: 2021/12/06 15:40:35 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	mini_final_clear(t_mini *ptr)
{
	mini_loop_clear(ptr);
	ft_lstclear(&ptr->env, pair_clear);
}

void	mini_loop_clear(t_mini *ptr)
{
	if (ptr->tree)
	{
		command_tree_free(ptr->tree);
		ptr->tree = NULL;
	}
	if (ptr->input)
	{
		free(ptr->input);
		ptr->input = NULL;
	}
	if (ptr->parse_error)
	{
		free(ptr->parse_error);
		ptr->parse_error = NULL;
	}
}

void	*clean_exit(void *ptr, char *err_msg, void (*free_fct)(void *))
{
	if (ptr && free_fct)
		free_fct(ptr);
	if (err_msg)
	{
		g_mini.status = 258;
		g_mini.parse_error = err_msg;
	}
	return (NULL);
}

char	*syntax_error_msg(t_token *token)
{
	char	*msg;
	char	*s;

	if (token)
		s = token->value;
	else
		s = "newline";
	s = ft_strjoin("syntax error near unexpected token `", s);
	msg = ft_strjoin(s, "'");
	free(s);
	return (msg);
}
