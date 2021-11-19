/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falmeida <falmeida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 12:00:13 by falmeida          #+#    #+#             */
/*   Updated: 2021/09/21 13:40:09 by falmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_signal(int signal)
{
	//signal == SIGQUIT
	if (signal == SIGINT)
	{
		write(1,"\n", 1);
		//rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
