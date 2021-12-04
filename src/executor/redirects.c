/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 10:20:23 by jpceia            #+#    #+#             */
/*   Updated: 2021/12/03 12:37:52 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <fcntl.h>

void	dup2_and_close(int new, int old)
{
	if (dup2(new, old) < 0)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(new);
}

void	set_fd_out(char *fname, bool append, int *fd)
{
	if (fname)
	{
		if (append)
			*fd = open(fname, O_WRONLY | O_APPEND | O_CREAT, 0644);
		else
			*fd = open(fname, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (*fd < 0)
		{
			perror(fname);
			exit(EXIT_FAILURE);
		}
	}
}

void	set_fd_in(char *fname, int *fd)
{
	if (fname)
	{
		*fd = open(fname, O_RDONLY);
		if (*fd < 0)
		{
			perror(fname);
			exit(EXIT_FAILURE);
		}
	}
}
