/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_quoted_words.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:22:38 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/22 14:30:47 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

static int	count_words(char *str, int i, int *unquoted, int *nb)
{
	int	j;

	if (str[i] == '\'' || str[i] == '"')
	{
		if (*unquoted)
			(*nb)++;
		*unquoted = 0;
		j = i + 1;
		while (str[j] != '\0')
		{
			if (str[j] == str[i])
			{
				(*nb)++;
				i = j;
				break ;
			}
			j++;
		}
	}
	else
		*unquoted = 1;
	i++;
	return (i);
}

/**
 * @brief Get the number of quoted words in a string.
 * 
 * @param str String to check.
 * @return Number of quoted words.
 */
int	get_nb_quoted_words(char *str)
{
	int	i;
	int	nb;
	int	len;
	int	unquoted;

	len = ft_strlen(str);
	nb = 0;
	i = 0;
	unquoted = 0;
	while (str[i] != '\0')
		i = count_words(str, i, &unquoted, &nb);
	if (str[len - 1] != '\'' && str[len - 1] != '"')
		nb++;
	if (len > 0 && nb == 0)
		nb++;
	return (nb);
}
