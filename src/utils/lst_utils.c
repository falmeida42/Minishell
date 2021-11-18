/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 17:32:09 by fferreir          #+#    #+#             */
/*   Updated: 2021/11/18 10:47:09 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_argv(void)
{
	int	x;
	int	y;

	x = 0;
	while (g_mini.argv[x] != NULL)
		x++;
	y = -1;
	while (++y < x)
	{
		free(g_mini.argv[y]);
		g_mini.argv[y] = NULL;
	}
	free(g_mini.argv);
}

void	free_struct(char *input)
{
	(void)input;
	ft_lstclear(&g_mini.env, pair_clear);
//	free(input);
	input = NULL;
//	free_argv(g_mini);
}
