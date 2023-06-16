/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_quoted_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:10:07 by cbernot           #+#    #+#             */
/*   Updated: 2023/06/16 11:16:44 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

static char	**init_tab(int size)
{
	char	**tab;
	int		i;

	tab = malloc(sizeof(char *) * (size + 1));
	if (!tab)
		return (0);
	i = 0;
	while (i < size)
	{
		tab[i] = 0;
		i++;
	}
	return (tab);
}

static int	get_first_cell(char *str, char **tab, int *cell, int *last_alloc)
{
	int		i;

	if (str[0] != '"' && str[0] != '\'')
	{
		i = 0;
		while (str[i] != '\0' && str[i] != '\'' && str[i] != '"')
			i++;
		tab[0] = ft_strndup(str, i);
		*cell = 1;
		*last_alloc = i - 1;
	}
	else
	{
		i = 0;
		*cell = 0;
	}
	return (i);
}

static void	keep_going(t_parse_param p, char **tab)
{
	if (*(p.i) != *(p.last_alloc) + 1)
	{
		tab[*(p.cell)] = ft_strndup(&(p.str)[*(p.last_alloc) + 1], *(p.i) \
			- *(p.last_alloc) - 1);
		*(p.cell)++;
		*(p.last_alloc) = *(p.i);
	}
}

static void	fill_cell(t_parse_param p, int j, char **tab)
{
	while ((p.str)[j] != '\0')
	{
		if ((p.str)[j] == (p.str)[*(p.i)])
		{
			tab[*(p.cell)] = ft_strndup(&(p.str)[*(p.i)], j - *(p.i) + 1);
			*(p.cell)++;
			*(p.last_alloc) = j;
			*(p.i) = j;
			break ;
		}
		j++;
	}
}

char	**fill_quoted_tab(char *str, int size)
{
	int				i;
	int				cell;
	char			**tab;
	int				last_alloc;
	t_parse_param	p;

	last_alloc = -1;
	tab = init_tab(size);
	if (!tab)
		return (0);
	i = get_first_cell(str, tab, &cell, &last_alloc) - 1;
	while (str[++i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			p = init_parse_p(str, &i, &last_alloc, &cell);
			keep_going(p, tab);
			fill_cell(p, i + 1, tab);
		}
	}
	if (!tab[size - 1])
		tab[size - 1] = get_last_unquoted(str);
	tab[size] = 0;
	return (tab);
}
