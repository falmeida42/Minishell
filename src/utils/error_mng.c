/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_mng.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 14:00:39 by fferreir          #+#    #+#             */
/*   Updated: 2021/11/18 03:04:23 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_output(char type)
{
	if (type == 'c')
		printf("minishell: command not found: %s\n", g_mini.argv[0]);
}
