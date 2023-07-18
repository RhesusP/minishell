/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recreate_new_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 11:42:13 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/18 22:58:20 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*join_path(char **tab, int size)
{
	char	*res;
	int		i;
	char	*temp;
	char	*temp1;

	res = 0;
	if (!tab[0])
		res = ft_strdup("/");
	i = 0;
	while (i < size)
	{
		if (tab[i])
		{
			temp = ft_strjoin("/", tab[i]);
			temp1 = ft_strjoin_nullable(res, temp);
			free(res);
			free(temp);
			res = ft_strdup(temp1);
			free(temp1);
		}
		i++;
	}
	return (res);
}

static void	free_cell(char **tab, int i)
{
	free(tab[i]);
	tab[i] = 0;
}

char	*recreate_new_path(char **tab, int size)
{
	int		i;
	int		j;

	i = -1;
	while (tab[++i] && i < size)
	{
		if (tab[i] && ft_strcmp(tab[i], ".") == 0)
			free_cell(tab, i);
		else if (tab[i] && ft_strcmp(tab[i], "..") == 0)
		{
			j = i - 1;
			while (j >= 0 && !tab[j])
				j--;
			if (j >= 0)
				free_cell(tab, j);
			free_cell(tab, i);
		}
	}	
	return (join_path(tab, size));
}
