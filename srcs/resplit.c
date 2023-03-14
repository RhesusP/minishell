/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resplit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:13:40 by cbernot           #+#    #+#             */
/*   Updated: 2023/03/12 17:03:51 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

static int	ft_get_nb_w(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s && s[i])
	{
		if (!is_unquoted_metachar(s, i))
		{
			count++;
			while (!is_unquoted_metachar(s, i) && s[i])
				i++;
		}
		else if (is_unquoted_metachar(s, i))
		{
			count++;
			i++;
		}
		else
			i++;
	}
	return (count);
}
/*
static char	**ft_malloc(char *s, int *count)
{
	char	**tab;
	int		count_m;

	*count = ft_get_nb_w(s);
	count_m = *count;
	tab = malloc((count_m + 1) * sizeof(char *));
	if (!tab)
		return (0);
	return (tab);
}
*/

static char	**ft_free_all(char **tab, int i)
{
	while (i > 0)
		free(tab[i--]);
	free(tab);
	return (0);
}
/*
char	**resplit(char *s)
{
	char	**tab;
	int		i;
	int		j;
	int		save;
	int		count;

	i = -1;
	j = 0;
	tab = ft_malloc((char *)s, &count);
	if (!tab)
		return (0);
	while (++i < count)
	{
		while (is_unquoted_metachar(s, j))
			j++;
		save = j;
		while (!is_unquoted_metachar(s, j) && s[j])
			j++;
		tab[i] = ft_substr(s, save, j - save);
		if (!tab[i])
			return (ft_free_all(tab, i));
		j++;
	}
	tab[count] = 0;
	printf("nb word: %d\n", count);
	return (tab);
}
*/

char	**resplit(char *s)
{
	char	**tab;
	int		count;
	int		i;

	tab = ft_malloc((char *)s, &count);
	
}