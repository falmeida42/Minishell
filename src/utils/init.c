/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 09:35:31 by jpceia            #+#    #+#             */
/*   Updated: 2021/12/08 15:26:48 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mini *mini_init(t_mini *ptr, char **envp)
{
	ptr->env = map_from_str_array(envp, '=');
	ptr->exit = false;
	ptr->parse_error = NULL;
	return (ptr);
}
