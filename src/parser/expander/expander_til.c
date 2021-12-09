/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_til.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 18:23:22 by jpceia            #+#    #+#             */
/*   Updated: 2021/12/07 19:39:25 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_til(char *str)
{
	char	*result;
	char	*home;

	if (str[1] != '/')
		return (str);
	home = env_get("HOME");
	if (!home)
		home = "";
	result = ft_strjoin(home, str + 1);
	free(str);
	return (result);
}

char	*ft_expander_til(t_token *token)
{
	char	*home;

	home = env_get("HOME");
	if (!home)
		home = "";
	if (!ft_strcmp(token->value, "~"))
		return (ft_strdup(home));
	return (check_til(token->value));
}
