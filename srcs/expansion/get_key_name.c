/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_key_name.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:35:01 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/22 14:29:46 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

/**
 * @brief Check if a char is a valid key name.
 * 
 * @param c 
 * @return 1 if the char is valid, 0 otherwise.
 */
static int	char_is_valid_key(char c)
{
	if (c != '\0' && (c == '_' || c == '?' || ft_isalnum(c)))
		return (1);
	return (0);
}

/**
 * @brief Get the first cell of the tab.
 * @details The first cell is the part of the string before the first '$'.
 * @param tab Tab to fill.
 * @param str String to expand.
 * @return Index of the first '$' in the string.
 */
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

/**
 * @brief Get the key name from a string.
 * @details The key name is the part of the string between the first '$' and the
 * first invalid char.
 * @param str String to expand.
 * @return A tab with the string before the key name, the key name and the string
 * after the key name.
 */
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
	if (len < (int)ft_strlen(str))
	{
		while (char_is_valid_key(str[len]) && str[len - 1] != '?')
			len++;
		tab[1] = ft_strndup(&str[i], len - i);
		if (len < (int)ft_strlen(str) && str[len])
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
