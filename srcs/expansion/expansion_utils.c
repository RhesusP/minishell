/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 17:15:19 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/22 14:04:36 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

/**
 * @brief Join a tab of strings into one string.
 * 
 * @param tab The tab to join.
 * @return char* The joined string.
 */
char	*values_to_str(char **tab)
{
	int		i;
	char	*res;
	char	*temp;

	i = 0;
	res = malloc(sizeof(char));
	res[0] = '\0';
	if (!tab)
		return (res);
	while (tab[i])
	{
		temp = ft_strjoin_nullable(res, tab[i]);
		free(res);
		res = ft_strdup(temp);
		free(temp);
		i++;
	}
	return (res);
}

/**
 * @brief Get the last unquoted part of a string.
 * 
 * @param str 
 * @return char* 
 */
char	*get_last_unquoted(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (i >= 0)
	{
		if (str[i] == '\'' || str[i] == '"')
			return (ft_strdup(&str[i + 1]));
		i--;
	}
	return (0);
}

/**
 * @brief Remove quotes from a string.
 * 
 * @param str The string to remove quotes from.
 * @return char* The string without quotes.
 */
char	*remove_quotes(char *str)
{
	int	len;
	int	size;

	len = ft_strlen(str);
	if (str[len - 1] == '\'' || str[len - 1] == '"')
		size = len - 2;
	else
		size = len - 1;
	return (ft_strndup(&str[1], size));
}

/**
 * @brief Join a tab of strings into one string.
 * 
 * @param tab The tab to join.
 * @param size The size of the tab.
 * @return char* The joined string.
 */
char	*join_tab(char **tab, int size)
{
	int		i;
	char	*res;
	char	*temp;

	res = 0;
	i = 0;
	while (i < size)
	{
		temp = ft_strjoin_nullable(res, tab[i]);
		if (res)
			free(res);
		res = ft_strdup(temp);
		free(temp);
		i++;
	}
	return (res);
}
