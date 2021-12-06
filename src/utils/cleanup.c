/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 17:32:09 by fferreir          #+#    #+#             */
/*   Updated: 2021/12/06 14:15:30 by jpceia           ###   ########.fr       */
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
	ptr->parse_error = NULL;
}

void	*clean_exit(void *ptr, char *err_msg, void (*free_fct)(void *))
{
	if (ptr && free_fct)
		free_fct(ptr);
	if (err_msg)
	{
		g_mini.status = 2;
		ft_putendl_error(err_msg);
	}
	return (NULL);
}
