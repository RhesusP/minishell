/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tubes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 21:13:18 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/21 16:57:45 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

/**
 * @brief Create an array of int* of size nb_tubes + 1.
 * 
 * @param nb_tubes 
 * @return int** 
 */
int	**create_tubes(int nb_tubes)
{
	int	i;
	int	**tubes;

	tubes = malloc(sizeof(int *) * (nb_tubes + 1));
	i = 0;
	while (i < nb_tubes)
	{
		tubes[i] = malloc(sizeof(int) * 2);
		if (pipe(tubes[i]) == -1)
			perror("pipe failed.\n");
		i++;
	}
	tubes[i] = 0;
	return (tubes);
}

/**
 * @brief Free the array of int*.
 * 
 * @param tubes 
 */
void	free_tubes(int **tubes)
{
	int	i;

	i = 0;
	while (tubes[i])
	{
		free(tubes[i]);
		i++;
	}
	free(tubes);
}
