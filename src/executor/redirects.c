/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 10:20:23 by jpceia            #+#    #+#             */
/*   Updated: 2021/12/06 12:01:25 by jpceia           ###   ########.fr       */
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

void	set_fd_out(t_outfile *out, int *fd)
{
	int	oflag;

	if (out)
	{
		oflag = O_WRONLY | O_CREAT;
		if (out->append)
			oflag |= O_APPEND;
		else
			oflag |= O_TRUNC;
		*fd = open(out->fname, oflag, 0644);
		if (*fd < 0)
		{
			perror(out->fname);
			exit(EXIT_FAILURE);
		}
	}
}

void	set_fd_in(t_infile *in, int *fd)
{
	int	fd_pipe[2];

	if (in->heredoc)
	{
		if (pipe(fd_pipe) < 0)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		*fd = fd_pipe[0];
		ft_putstr_fd(in->data, fd_pipe[1]);
		ft_putchar_fd(0, fd_pipe[1]);
		close(fd_pipe[1]);
	}
	else
	{
		*fd = open(in->data, O_RDONLY);
		if (*fd < 0)
		{
			perror(in->data);
			exit(EXIT_FAILURE);
		}
	}
}

void	set_fd_out_list(t_list *outfiles, int *fd)
{
	t_outfile	*out;
	t_list		*lst;

	lst = outfiles;
	while (lst)
	{
		out = (t_outfile *)lst->content;
		set_fd_out(out, fd);
		lst = lst->next;
		if (lst)
			close(*fd);
	}
}

void	set_fd_in_list(t_list *infiles, int *fd)
{
	t_infile	*in;
	t_list		*lst;

	lst = infiles;
	while (lst)
	{
		in = (t_infile *)lst->content;
		set_fd_in(in, fd);
		lst = lst->next;
		if (lst)
			close(*fd);
	}
}
