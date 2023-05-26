/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 20:45:18 by cbernot           #+#    #+#             */
/*   Updated: 2023/05/26 10:41:50 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

/**
 * @brief Checks that all quotes are closed
 * @return 1 if there is an unclosed quote, else returns 0
*/
int	check_quotes_err(char *line)
{
	int	nb_single;
	int	nb_double;
	int	i;

	nb_single = 0;
	nb_double = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\'')
			nb_single++;
		else if (line[i] == '"')
			nb_double++;
		i++;
	}
	if (nb_double % 2 != 0 || nb_single % 2 != 0)
		return (0);
	return (1);
}
