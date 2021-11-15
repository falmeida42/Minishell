/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 11:24:46 by fferreir          #+#    #+#             */
/*   Updated: 2021/11/15 19:49:02 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_envnew_pp(char **content)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->name = content[0];
	new->content = content[1];
	new->next = NULL;
	return (new);
}

void	ft_envnode_print(t_env *lst, char *name)
{
	t_env	*head;

	head = lst;
	while (1)
	{
		if (str_cmp_both_len(lst->name, name))
			printf("Content=|%s|, Name=|%s|, PREV=|%p| ADD=|%p| Next=|%p|\n",
				(char *)lst->content,
				(char *)lst->name,
				lst->prev, lst, lst->next);
		if (lst->next == NULL)
			break ;
		lst = lst->next;
	}
	lst = head;
}

char	*get_name(char *str, char c)
{
	char	*name;
	int 	x;

	x = -1;
	if (!str)
		return(NULL);
	name = malloc(sizeof(char *) * (ft_strlen(str) + 1));
	if (name == NULL)
		return (NULL);
	while (str[++x] && str[x] != c)
		name[x] = str[x];
	name[x] = '\0';
	return (name);
}

void	env_add_names(t_env *lst)
{
	t_env	*head;

	head = lst;
	while (lst)
	{
		lst->name = get_name(lst->content, '=');
		if (lst->next == NULL)
			break ;
		lst = lst->next;
	}
	lst = head;
}

t_env	*get_env(char **env)
{
	t_env	*temp;
	int x;

	x = -1;
	mini.env = NULL;
	while (env[++x] != NULL)
	{
		temp = ft_envnew_pp(ft_split(env[x], '='));
		ft_envadd_back(&mini.env, temp);
	}
	return(mini.env);
}

void	ft_env()
{
	ft_envprint(mini.env, 'a');
}
