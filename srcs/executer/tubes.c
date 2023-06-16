/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tubes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 21:13:18 by cbernot           #+#    #+#             */
/*   Updated: 2023/06/16 11:18:13 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

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
