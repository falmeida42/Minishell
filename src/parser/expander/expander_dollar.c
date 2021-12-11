/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_dollar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 19:35:38 by jpceia            #+#    #+#             */
/*   Updated: 2021/12/11 14:16:22 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_strings(char *prefix, char *str, char *aux)
{
	free(prefix);
	free(str);
	free(aux);
}

char	*replace_dollar_generic(char *str, int i)
{
	char	*prefix;
	char	*aux;
	char	*value;
	int		shift;
	int		j;

	j = i + 1;
	while (str[j] != '\0' && !(ft_isspace(str[j])
			|| ft_contains(str[j], "'${\\\"")))
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
	value = ft_strjoin(aux, str + j + shift);
	free_strings(prefix, str, aux);
	return (value);
}

void	*bad_substitution_error(void)
{
	g_mini.parse_error = ft_strdup("bad substitution");
	g_mini.status = 1;
	return (NULL);
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
		return (bad_substitution_error());
	aux = ft_substr(str, i + 2, j - i - 2);
	value = env_get(aux);
	free(aux);
	if (!value)
		value = "";
	prefix = ft_substr(str, 0, i);
	aux = ft_strjoin(prefix, value);
	value = ft_strjoin(aux, str + j + 1);
	free_strings(prefix, str, aux);
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
	free_strings(prefix, str, aux);
	free(nb);
	return (result);
}
