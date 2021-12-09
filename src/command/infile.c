/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 21:36:04 by jpceia            #+#    #+#             */
/*   Updated: 2021/12/09 09:55:56 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	infile_heredoc_setup(t_infile *infile, char *eof)
{
	char	*holder;
	char	*line;

	infile->data = ft_strdup("");
	while (42)
	{
		line = readline("> ");
		if (!ft_strcmp(line, eof))
			break ;
		holder = infile->data;
		infile->data = ft_strjoin(holder, line);
		infile->data = ft_straddc(infile->data, '\n');
		free(line);
	}
	infile->heredoc = true;
}

t_infile	*infile_new(char *value, bool heredoc)
{
	t_infile	*infile;

	infile = malloc(sizeof(*infile));
	if (!infile)
		return (NULL);
	if (heredoc)
		infile_heredoc_setup(infile, value);
	else
	{
		infile->data = ft_strdup(value);
		infile->heredoc = false;
	}
	return (infile);
}

void	infile_free(void *ptr)
{
	t_infile	*infile;

	infile = (t_infile *)ptr;
	free(infile->data);
	free(infile);
}

void	infile_print(t_infile *infile)
{
	if (infile->heredoc)
		ft_putstr("heredoc:\n");
	else
		ft_putstr("infile: ");
	ft_putstr(infile->data);
	ft_putchar('\n');
}
