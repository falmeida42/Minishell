/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 10:20:23 by jpceia            #+#    #+#             */
/*   Updated: 2021/12/02 10:24:22 by jpceia           ###   ########.fr       */
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

void set_fd_out(char *fname, bool append, int *old, int *new)
{
	if (fname)
	{
		if (*old)
			*old = dup(STDOUT_FILENO);
		if (append)
			*new = open(fname, O_WRONLY | O_APPEND | O_CREAT, 0644);
		else
			*new = open(fname, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (*new < 0)
		{
			perror(fname);
			exit(EXIT_FAILURE);
		}
		dup2_and_close(*new, STDOUT_FILENO);
	}
}

void set_fd_in(char *fname, int *old, int *new)
{
	if (fname)
	{
		if (*old)
			*old = dup(STDIN_FILENO);
		*new = open(fname, O_RDONLY);
		if (*new < 0)
		{
			perror(fname);
			exit(EXIT_FAILURE);
		}
		dup2_and_close(*new, STDIN_FILENO);
	}
}
