/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 20:47:38 by cbernot           #+#    #+#             */
/*   Updated: 2023/03/18 20:49:54 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

char	*print_type(t_type type)
{
	if (type == CMD)
		return ("CMD");
	else if (type == ARG)
		return ("ARG");
	else if (type == PIPE)
		return ("PIPE");
	else if (type == RI)
		return ("RI");
	else if (type == RO)
		return ("RO");
	else if (type == ARO)
		return ("ARO");
	else if (type == HE)
		return ("HE");
	else if (type == FILEPATH)
		return ("FILEPATH");
	else if (type == DELIMITER)
		return ("DELIMITER");
	else if (type == IGN)
		return ("IGN");
	else if (type == INIT)
		return ("INIT");
}

