/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 09:35:31 by jpceia            #+#    #+#             */
/*   Updated: 2021/12/11 17:19:11 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mini	*mini_init(t_mini *ptr, char **envp)
{
	ptr->env = map_from_str_array(envp, '=');
	ptr->exit = false;
	ptr->parse_error = NULL;
	ptr->pid = 0;
	ptr->is_child = false;
	ptr->prompt = "minishell: ";
	if (tcgetattr(STDIN_FILENO, &g_mini.term) != 0)
		ft_putendl_error("Error: tcgetattr");
	g_mini.term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &g_mini.term) != 0)
		ft_putendl_error("Error: tcsetattr");
	return (ptr);
}
