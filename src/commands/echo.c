/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 18:35:15 by falmeida          #+#    #+#             */
/*   Updated: 2021/11/18 02:06:12 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Output the args, separated by spaces, followed by a newline.
 * If -n is specified, the trailing newline is suppressed.
 * The return status is 0 unless a write error occurs. 
 */

/*
void	print_env_content(t_env *lst, char *name)
{
	char *content;

	content = NULL;
	if (return_env_content(lst, name))
	{
		content = return_env_content(lst, name);
		printf("%s",content);
	}
	free(name);
}

char	*return_env_content(t_env *lst, char *name)
{
	while (lst)
	{
		if (str_cmp_both_len(lst->name, name))
			break ;
		lst = lst->next;
	}
	return (lst->content);
}

char	*env_flag_check(int i)
{
	char	*env_name;
	int j;

	j = 0;
	env_name = NULL;
	while (mini.argv[i][j])
		j++;
	if (j > 0 && mini.argv[i][0] == '$')
	{
		env_name = ft_substr(mini.argv[i], 1, j);
		return (env_name);
	}
	return (NULL);
}
*/

void	echo_n_flag(void)
{
	int	index;

	index = 1;
	if (mini.argv[index] == NULL)
		return ;
	while (mini.argv[index + 1])
	{
		ft_putstr(mini.argv[index]);
		ft_putchar(' ');
		++index;
	}
	ft_putstr(mini.argv[index]);
}

void	ft_echo()
{
	if (mini.argv[1] && ft_strcmp(mini.argv[1], "-n") == 0)
		echo_n_flag();
	else
	{
		echo_n_flag();
		ft_putchar('\n');
	}
	// return 0
}
