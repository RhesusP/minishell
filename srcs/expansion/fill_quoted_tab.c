/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_quoted_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:51:03 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/19 09:25:53 by cbernot          ###   ########.fr       */
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

static int	get_first_word(char *str, char ***tab, int *cell, int *last_alloc)

{
	int	i;

	i = 0;
	*last_alloc = -1;
	*cell = 0;
	if (str[0] != '"' && str[0] != '\'')
	{
		while (str[i] != '\0' && str[i] != '\'' && str[i] != '"')
			i++;
		(*tab)[0] = ft_strndup(str, i);
		*cell = 1;
		*last_alloc = i - 1;
	}
	return (i);
}

static t_parse_p	sub_fill_quoted_tab(t_parse_p *p, char **tab, int j)
{
	while (p->str[j] != '\0')
	{
		if (p->str[j] == p->str[p->i])
		{
			tab[p->cell] = ft_strndup(&p->str[p->i], j - p->i + 1);
			p->cell++;
			p->l_a = j;
			p->i = j;
			break ;
		}
		j++;
	}
	return (*p);
}

t_parse_p	init_param(char *str)
{
	t_parse_p	param;

	param.str = str;
	param.l_a = 0;
	param.cell = 0;
	return (param);
}

char	**fill_quoted_tab(char *str, int size)
{
	t_parse_p	p;
	char		**tab;

	p = init_param(str);
	tab = init_tab(size);
	p.i = get_first_word(p.str, &tab, &p.cell, &p.l_a);
	while (p.str[p.i] != '\0')
	{
		if (p.str[p.i] == '\'' || p.str[p.i] == '"')
		{
			if (p.i != p.l_a + 1)
			{
				tab[p.cell] = ft_strndup(&p.str[p.l_a + 1], p.i - p.l_a - 1);
				p.cell++;
				p.l_a = p.i;
			}
			p = sub_fill_quoted_tab(&p, tab, p.i + 1);
		}
		p.i++;
	}
	if (!tab[size - 1])
		tab[size - 1] = get_last_unquoted(str);
	tab[size] = 0;
	return (tab);
}
