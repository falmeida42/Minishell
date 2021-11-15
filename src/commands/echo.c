/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 18:35:15 by falmeida          #+#    #+#             */
/*   Updated: 2021/11/15 19:49:52 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	echo_no_flag(int i, int j)
{
	if (i > 1)
	{
		j = 1;
		while (i > j)
		{
			if (env_flag_check(j) != NULL)
				print_env_content(mini.env, env_flag_check(j));
			else
				printf("%s", mini.argv[j]);
			if (i > 1 + j++)
				printf(" ");
		}
		printf("\n");
	}
}

void	echo_n_flag(int i, int j)
{
	if (i > 2)
	{
		j = 2;
		while (i > j)
		{
			if (env_flag_check(j) != NULL)
				print_env_content(mini.env, env_flag_check(j));
			else
				printf("%s", mini.argv[j]);
			if (i > 1 + j++)
				printf(" ");
		}
	}
}

void	ft_echo()
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (mini.argv[i])
		i++;
	if (i >= 2 && str_cmp_both_len(mini.argv[1], "-n"))
		echo_n_flag(i, j);
	else
		echo_no_flag(i, j);
}
