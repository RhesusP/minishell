/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:53:15 by cbernot           #+#    #+#             */
/*   Updated: 2023/03/12 16:09:27 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	ft_get_next_word(char *str, char *charset, int *i)
{
	int	j;

	while (charset[0] == '\0' && str[*i] != '\0')
		*i += 1;
	while (str[*i] != '\0')
	{
		j = 0;
		while (charset[j] != '\0')
		{
			if (str[*i] == charset[j] && is_unquoted(str, *i))
				return (1);
			j++;
		}
		*i += 1;
	}
	return (0);
}

char	**ft_fill_tab(char **tab, char *str, char *charset)
{
	int	i;
	int	temp;
	int	j;
	int	l;
	int	next;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		temp = i;
		next = ft_get_next_word(str, charset, &i);
		if (i - temp != 0)
		{
			tab[j] = malloc(sizeof(char) * (i - temp + 1));
			if (!tab[j])
				return (NULL);
			l = 0;
			while (temp < i)
				tab[j][l++] = str[temp++];
			tab[j++][l] = '\0';
		}
		i += next;
	}
	return (tab);
}

char	**ft_strtok(char *str, char *charset)
{
	char	**result;
	int		i;
	int		temp;
	int		next;
	int		size;

	i = 0;
	size = 0;
	while (str[i] != '\0')
	{
		temp = i;
		next = ft_get_next_word(str, charset, &i);
		if (i - temp != 0)
			size++;
		i += next;
	}
	result = malloc(sizeof(char *) * (size + 1));
	if (!result)
		return (NULL);
	result[size] = malloc(sizeof(char));
	result[size] = NULL;
	return (ft_fill_tab(result, str, charset));
}