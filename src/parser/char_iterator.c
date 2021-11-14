/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_iterator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 06:15:38 by jpceia            #+#    #+#             */
/*   Updated: 2021/11/14 06:15:57 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char char_iterator_peek(char_iterator *it)
{
    return (**it);
}

char char_iterator_next(char_iterator *it)
{
    return (*(++*it));
}
