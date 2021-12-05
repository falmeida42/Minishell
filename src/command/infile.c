/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 21:36:04 by jpceia            #+#    #+#             */
/*   Updated: 2021/12/04 22:07:08 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_infile	*infile_new(char *value, bool heredoc)
{
	t_infile	*infile;
	char		*line;
	char		*holder;

	infile = malloc(sizeof(*infile));
	if (!infile)
		return (NULL);
	if (heredoc)
	{
		infile->data = ft_strdup("");
		while (42)
		{
			line = readline("> ");
			if (!ft_strcmp(line, value))
				break;
			holder = infile->data;
			infile->data = ft_strjoin(holder, line);
			infile->data = ft_straddc(infile->data, '\n');
			free(line);
		}
		infile->heredoc = true;
	}
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
