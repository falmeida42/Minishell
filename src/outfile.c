/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 15:11:45 by jpceia            #+#    #+#             */
/*   Updated: 2021/12/04 16:12:47 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_outfile	*outfile_new(char *fname, bool append)
{
	t_outfile	*outfile;

	outfile = malloc(sizeof(*outfile));
	if (!outfile)
		return (NULL);
	outfile->fname = ft_strdup(fname);
	outfile->append = append;
	return (outfile);
}

void	outfile_free(void *ptr)
{
	t_outfile	*outfile;

	outfile = (t_outfile *)ptr;
	free(outfile->fname);
	free(outfile);
}
