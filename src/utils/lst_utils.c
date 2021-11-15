/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 17:32:09 by fferreir          #+#    #+#             */
/*   Updated: 2021/11/15 20:13:27 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_dp_env(t_env *lst)
{
	t_env *temp;

	if (!lst)
		return ;
	while (lst)
	{
		temp = lst->next;
		free(lst);
		lst = NULL;
		lst = temp;
	}
}

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

void	free_env(t_env *lst)
{
	if (lst == NULL)
	{
		free(lst);
		lst = NULL;
		return ;
	}
	while(1)
	{
		printf("%s %p\n", (char *)lst->content, (char *)lst->content);
		free(lst->content);
		lst->content = NULL;
		free(lst->name);
		lst->name = NULL;
		if (lst->next == NULL)
		{
			free(lst);
			lst = NULL;
			break ;
		}
		lst = lst->next;
	}
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
