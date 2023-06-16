/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_quoted_words.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 09:49:36 by cbernot           #+#    #+#             */
/*   Updated: 2023/06/16 16:56:09 by cbernot          ###   ########.fr       */
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

int	get_nb_quoted_words(char *str)
{
	int	i;
	int	j;
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
