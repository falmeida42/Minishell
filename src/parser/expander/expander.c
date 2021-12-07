/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 18:29:58 by jpceia            #+#    #+#             */
/*   Updated: 2021/12/07 11:58:44 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

void	*expand_operation(void *content)
{
	t_token	*token;
	bool	check;

	token = (t_token *) content;
	if (!token || !is_word_token(token))
		return (token);
	check = token->type == TOKEN_DQUOTED || token->type == TOKEN_TEXT;
	if (check && ft_contains('$', token->value))
		token->value = ft_expander(token->value);
	if (token->type == TOKEN_TEXT && *token->value == '~')
		token->value = ft_expander_til(token);
	return (token);
}

char	*cmp_env(char *value)
{
	if (ft_contains('{',  value))
		return (cmp_brekets((ft_substr(value, 1, ft_strlen(value) - 2))));
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

	result = malloc(sizeof(char) * (ft_strlen(str) - size) + (ft_strlen(expand) + 1000));
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
				if (str[i] == ' ' || str[i] == '"' || str[i] == '\'' || str[i] == '{' || str[i + 1] == '$')
				{
					if (str[i] == '{')
						while (str[i - 1] != '}')
							i++;
					else
						i++;
					break ;
				}
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
		if (str[j] == ' ' || str[j] == '\'' || str[j] == '"' || str[j] == '{' || str[j + 1] == '$')
		{
			if (str[j] == '{')
				while (str[j] != '}')
					j++;
			break ;
		}
		j++;
	}
	dollar_size = j - i;
	if (str[j] == '}' || str[j + 1] == '$')
		value = ft_substr(str, i + 1, j - (i));
	else
		value = ft_substr(str, i + 1, j - (i + 1));	
	expand = cmp_env(value);
	if (expand == NULL)
		return (ft_strdup(""));
	return (join_dollar(str, expand, dollar_size));
}

char	*replace_dollar_status(char *str, int i)
{
	char	*result;
	char	*prefix;
	char	*aux;
	char	*nb;

	prefix = ft_substr(str, 0, i);
	nb = ft_itoa(g_mini.status);
	aux = ft_strjoin(prefix, nb);
	result = ft_strjoin(aux, str + i + 2);
	free(prefix);
	free(aux);
	free(nb);
	return (result);
}

int		needs_to_replace_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && !ft_contains(str[i+1], " \0\""))
			return (1);
		i++;
	}
	return (0);
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
			if (str[i+1] == '?')
				result = replace_dollar_status(str, i);
			else
				result = check_dollar(str, i);
			break ;
		}
		i++;
	}
	if (needs_to_replace_dollar(result))
		return (ft_expander(result));
	return (result);
}