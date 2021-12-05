/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 18:29:58 by jpceia            #+#    #+#             */
/*   Updated: 2021/11/18 21:14:24 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

char	*cmp_env(char *value)
{
	if (!ft_strcmp(value, "\?"))
		return (ft_strdup(ft_itoa(g_mini.status)));
	else if (env_get(value) == NULL)
		return(ft_strdup(""));
	else
		return (ft_strdup(env_get(value)));
}

char	*join_dollar(char *str, char *expand, int size)
{
	int	i;
	int	j;
	int	z;
	int	x;
	int	first;
	char	*result;

	result = malloc(sizeof(char) * (ft_strlen(str) - size) + (ft_strlen(expand)));
	i = 0;
	j = 0;
	z = 0;
	x = (ft_strlen(str) - size) + (ft_strlen(expand));
	first = 1;
	while (x > 0)
	{
		if (str[i] == '$' && first == 1)
		{
			first++;
			while (str[i] != '\0')
			{
				if (str[i] == ' ' || str[i] == '"' || str[i] == '\'')
					break ;
				i++;
			}
			while (expand[z] != '\0')
			{
				result[j] = expand[z];
				j++;
				z++;
				x--;
			}
		}
		if (str)
			result[j] = str[i];
		i++;
		j++;
		x--;
	}
	result[j] = '\0';
	return (result);
}

char	*check_dollar(char *str, int i)
{
	char	*value;
	char	*expand;
	int	j;
	int	dollar_size;

	j = i;
	while (str[j] != '\0')
	{
		if (str[j] == ' ' || str[j] == '\'' || str[j] == '"')
			break ;
		j++;
	}
	dollar_size = j - i;
	value = ft_substr(str, i + 1, j - (i + 1));
	expand = cmp_env(value);
	if (expand == NULL)
		return (ft_strdup(""));
	return (join_dollar(str, expand, dollar_size));
}

char	*ft_expander(char *str)
{
	char	*result;
	int	i;
	i = 0;
	result = NULL;

	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			result = check_dollar(str, i);
			break ;
		}
		i++;
	}
	if (ft_contains('$', result))
		return (ft_expander(result));
	return (result);
}