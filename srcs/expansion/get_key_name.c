/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_key_name.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:35:01 by cbernot           #+#    #+#             */
/*   Updated: 2023/06/21 18:49:51 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

static int	char_is_valid_key(char c)
{
	if (c != '\0' && (c == '_' || c == '?' || ft_isalnum(c)))
		return (1);
	return (0);
}

static int	get_first_cell(char ***tab, char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0' && str[i] != '$')
		i++;
	if (i > 0)
		(*tab)[0] = ft_strndup(str, i);
	else
		(*tab)[0] = 0;
	return (i);
}

char	**get_key_name(char *str)
{
	int		len;
	int		i;
	char	**tab;

	tab = malloc(sizeof(char *) * 3);
	if (!tab)
		return (0);
	i = get_first_cell(&tab, str);
	len = i + 1;
	if (len < ft_strlen(str))
	{
		while (char_is_valid_key(str[len]))
			len++;
		tab[1] = ft_strndup(&str[i], len - i);
		if (len < ft_strlen(str) && str[len])
			tab[2] = ft_strdup(&str[len]);
		else
			tab[2] = 0;
	}
	else
	{
		tab[1] = 0;
		tab[2] = 0;
	}
	return (tab);
}