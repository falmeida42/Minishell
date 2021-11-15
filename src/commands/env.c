/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 11:24:46 by fferreir          #+#    #+#             */
/*   Updated: 2021/11/15 18:19:19 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_lstnew_pp(char **content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->name = content[0];
	new->content = content[1];
	new->next = NULL;
	return (new);
}

void	ft_lstnode_print(t_list *lst, char *name)
{
	t_list	*head;

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
	while (str[++x] && str[x] != c)
		name[x] = str[x];
	name[x] = '\0';
	return(name);
}

void	env_add_names(t_list *lst)
{
	t_list	*head;

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

t_list	*get_env(char **env)
{
	t_list	*temp;
	int x;

	x = -1;
	mini.env = NULL;
	while (env[++x] != NULL)
	{
		temp = ft_lstnew_pp(ft_split(env[x], '='));
		ft_lstadd_back(&mini.env,temp);
	}
	return(mini.env);
}

void	ft_env()
{
	ft_lstprint(mini.env, 'a');
}
