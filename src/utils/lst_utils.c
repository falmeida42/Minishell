/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 17:32:09 by fferreir          #+#    #+#             */
/*   Updated: 2021/11/16 17:29:33 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_argv()
{
	int x;
	int y;

	x = 0;
	while (mini.argv[x] != NULL)
		x++;
	y = -1;
	while (++y < x)
	{
		free(mini.argv[y]);
		mini.argv[y] = NULL;
	}
	free(mini.argv);
}

void	free_struct(char *input)
{
	(void)input;
	free(mini.env);
	mini.env = NULL;
//	free(input);
	input = NULL;
//	free_argv(mini);
}
