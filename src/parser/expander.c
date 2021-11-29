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
#include "libft.h"
#include <dirent.h>

char	*cmp_env(char *value)
{
	char	*expanded;
	
	if (env_get(value) == NULL)
	{
		free(value);
		return(NULL);
	}
	else
	{
		expanded = env_get(value);
		free(value);
		return (expanded);
	}
}

char	*join_dollar(char *str, char *expand, int size)
{
	int	i;
	int	j;
	int	z;
	char	*result;

	result = malloc(sizeof(char) * (ft_strlen(str) - size) + (ft_strlen(expand)));
	i = 0;
	j = 0;
	z = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			while (str[i] != ' ' || str != '\0')
				i++;
			while (expand[z] != '\0')
			{
				result[j] = expand[z];
				j++;
				z++;
			}
		}
		result[j] = str[i];
		i++;
		j++;
	}
	result[j] = '\0';
	free(expand);
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
		if (str[j] == ' ')
			break ;
		i++;
	}
	dollar_size = j - i;
	value = ft_substr(str, i, j);
	expand = cmp_env(value);
	return (join_dollar(str, expand, dollar_size));
}

int	ft_expander(char *str)
{
	char	*result;
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
			check_dollar(str, i);
		i++;
	}
	printf("%s\n", result);
	return (0);
}
