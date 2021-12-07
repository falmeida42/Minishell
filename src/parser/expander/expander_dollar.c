/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_dollar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 19:35:38 by jpceia            #+#    #+#             */
/*   Updated: 2021/12/07 19:35:51 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace_dollar_generic(char *str, int i)
{
	char	*prefix;
	char	*aux;
	char	*value;
	int		shift;
	int		j;

	j = i + 1;
	while (str[j] != '\0' && !ft_contains(str[j], " \t${\\"))
		j++;
	shift = 0;
	if (str[j] == ' ')
		shift = 1;
	aux = ft_substr(str, i + 1, j - i - 1);
	value = env_get(aux);
	free(aux);
	if (!value)
		value = "";
	prefix = ft_substr(str, 0, i);
	aux = ft_strjoin(prefix, value);
	free(prefix);
	value = ft_strjoin(aux, str + j + shift);
	free(aux);
	return (value);
}

char	*replace_dollar_brackets(char *str, int i)
{
	char	*prefix;
	char	*aux;
	char	*value;
	int		j;

	j = i + 1;
	while (str[j] != '\0' && str[j] != '}' && str[j] != ' ')
		j++;
	if (str[j] != '}')
	{
		g_mini.parse_error = ft_strdup("bad substitution");
		g_mini.status = 1;
		return (NULL);
	}
	aux = ft_substr(str, i + 2, j - i - 2);
	value = env_get(aux);
	free(aux);
	if (!value)
		value = "";
	prefix = ft_substr(str, 0, i);
	aux = ft_strjoin(prefix, value);
	free(prefix);
	value = ft_strjoin(aux, str + j + 1);
	free(aux);
	return (value);
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
