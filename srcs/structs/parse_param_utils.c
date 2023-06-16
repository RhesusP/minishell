/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_param_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 09:42:33 by cbernot           #+#    #+#             */
/*   Updated: 2023/06/16 09:47:08 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

t_parse_param	init_parse_p(char *str, int *i, int *last_alloc, int *cell)
{
	t_parse_param	p;

	p.str = str;
	p.i = i;
	p.last_alloc = last_alloc;
	p.cell = cell;
	return (p);
}
