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

char    *cmp_brekets(char *str)
{
	char	*var;

    if (ft_contains(' ', str))
    {
        g_mini.parse_error = ft_strdup("bad substitution");
        return ("");
    }
    var = env_get(str);
	if (!var)
		return ("");
    return (var);
}

char	*cmp_env(char *value)
{
	char	*var;
	char	*result;

	if (ft_contains('{',  value))
	{
		var = ft_substr(value, 1, ft_strlen(value) - 2);
		result = cmp_brekets(var);
		free(var);
		return (result);
	}
	var = env_get(value);
	if (!var)
		return ("");
	return (var);
}

char	*check_dollar(char *str, int i)
{
	char	*prefix;
	char	*aux;
	char	*result;
	char	*key;
	int		j;

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
	//if (dollar_size == 1)
	//	return (ft_strdup(str));
	if (str[j] == '}' || str[j + 1] == '$')
		key = ft_substr(str, i + 1, j - (i));
	else
		key = ft_substr(str, i + 1, j - (i + 1));
	// ft_putchar('"');
	// ft_putstr(value);
	// ft_putchar('"');
	// ft_putnbr(dollar_size);
	// ft_putchar('\n');
	
	prefix = ft_substr(str, 0, i);
	aux = ft_strjoin(prefix, cmp_env(key));
	result = ft_strjoin(aux, str + j + 1);
	free(key);
	free(prefix);
	free(aux);
	// free(str)
	return (result);
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
	result = str;

	if (!needs_to_replace_dollar(str))
		return (str);

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
	return (ft_expander(result));
}