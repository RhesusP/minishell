/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resplit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:13:40 by cbernot           #+#    #+#             */
/*   Updated: 2023/05/17 10:13:07 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

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
			while (s[i] && !is_unquoted_metachar(s, i))
				i++;
		}
		else if (is_unquoted_double_chevron(s, i))
		{
			count++;
			i += 2;
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

static char	**ft_malloc(char *s, int *count)
{
	char	**tab;
	int		count_m;

	*count = ft_get_nb_w(s);
	count_m = *count;
	tab = malloc((count_m + 1) * sizeof(char *));
	if (!tab)
		return (0);
	tab[count_m] = NULL;
	return (tab);
}

char	**resplit(char *s)
{
	char	**tab;
	int		count;
	int		i;
	int		j;
	int		n_word;

	n_word = 0;
	tab = ft_malloc((char *)s, &count);
	// printf("nb word: %d\n", count);
	i = 0;
	while (n_word < count && i < ft_strlen(s))
	{
		if (is_unquoted_double_chevron(s, i))
		{
			tab[n_word] = ft_strndup(&s[i], 2);
			n_word++;
			i += 2;
		}
		else if (is_unquoted_metachar(s, i))
		{
			tab[n_word] = ft_strndup(&s[i], 1);
			n_word++;
			i++;
		}
		else
		{
			j = i;
			while (s[j] != '\0' && !is_unquoted_metachar(s, j))
				j++;
			tab[n_word] = ft_strndup(&s[i], j - i);
			i = j;
			n_word++;
		}
	}
	return (tab);
}
