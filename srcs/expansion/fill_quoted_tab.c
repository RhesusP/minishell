/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_quoted_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:51:03 by cbernot           #+#    #+#             */
/*   Updated: 2023/06/21 18:54:06 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

static char	**init_tab(int size)
{
	char	**tab;
	int		i;

	i = 0;
	tab = malloc(sizeof(char *) * (size + 1));
	if (!tab)
		return (0);
	while (i < size)
	{
		tab[i] = 0;
		i++;
	}
	return (tab);
}

char	**fill_quoted_tab(char *str, int size)
{
	int		i;
	int		j;
	int		cell;
	char	**tab;
	int		last_alloc;

	last_alloc = -1;
	tab = init_tab(size);
	cell = 0;
	if (str[0] != '"' && str[0] != '\'')
	{
		i = 0;
		while (str[i] != '\0' && str[i] != '\'' && str[i] != '"')
			i++;
		tab[0] = ft_strndup(str, i);
		cell = 1;
		last_alloc = i - 1;
	}
	else
		i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			if (i != last_alloc + 1)
			{
				tab[cell] = ft_strndup(&str[last_alloc + 1], i - last_alloc - 1);
				cell++;
				last_alloc = i;
			}
			j = i + 1;
			while (str[j] != '\0')
			{
				if (str[j] == str[i])
				{
					tab[cell] = ft_strndup(&str[i], j - i + 1);
					cell++;
					last_alloc = j;
					i = j;
					break ;
				}
				j++;
			}
		}
		i++;
	}
	if (!tab[size - 1])
		tab[size - 1] = get_last_unquoted(str);
	tab[size] = 0;
	return (tab);
}
