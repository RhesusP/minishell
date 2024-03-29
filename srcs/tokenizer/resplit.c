/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resplit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:13:40 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/22 16:55:56 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

static int	update_nb_w(char *s, int i, int *count)
{
	if (!is_unquoted_metachar(s, i))
	{
		(*count)++;
		while (s[i] && !is_unquoted_metachar(s, i))
			i++;
	}
	else if (is_unquoted_double_chevron(s, i))
	{
		(*count)++;
		i += 2;
	}
	else if (is_unquoted_metachar(s, i))
	{
		(*count)++;
		i++;
	}
	else
		i++;
	return (i);
}

static int	ft_get_nb_w(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s && s[i])
		i = update_nb_w(s, i, &count);
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

static void	sub_resplit(char *s, char **tab, int *n_word, int *i)
{
	int	j;

	if (is_unquoted_double_chevron(s, *i))
	{
		tab[(*n_word)] = ft_strndup(&s[*i], 2);
		(*n_word)++;
		*(i) += 2;
	}
	else if (is_unquoted_metachar(s, *i))
	{
		tab[(*n_word)] = ft_strndup(&s[*i], 1);
		(*n_word)++;
		*i += 1;
	}
	else
	{
		j = *i;
		while (s[j] != '\0' && !is_unquoted_metachar(s, j))
			j++;
		tab[(*n_word)] = ft_strndup(&s[*i], j - *i);
		*i = j;
		(*n_word)++;
	}
}

/**
 * @brief Split a string into words, taking into account the metacharacters.
 * This function is a subfunction of the `detect_close_pipe()` and 
 * `parse_word()` functions.
 * @param s 
 * @return char** 
 */
char	**resplit(char *s)
{
	char	**tab;
	int		count;
	int		i;
	int		n_word;

	n_word = 0;
	tab = ft_malloc((char *)s, &count);
	i = 0;
	while (n_word < count && i < (int)ft_strlen(s))
		sub_resplit(s, tab, &n_word, &i);
	return (tab);
}
