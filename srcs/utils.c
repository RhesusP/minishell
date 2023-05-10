/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:39:26 by cbernot           #+#    #+#             */
/*   Updated: 2023/05/03 11:06:50 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

char	*ft_strndup(const char *s1, unsigned int size)
{
	char			*res;
	unsigned int	i;

	res = malloc(sizeof(char) * (size + 1));
	if (!res)
		return (res);
	i = 0;
	while (i < size && s1[i] != '\0')
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_strnchr(const char *s, int c, int pos)
{
	int	i;
	int nb_occur;

	nb_occur = 0;
	i = 0;
	while ((unsigned char)s[i] != '\0')
	{
		// printf("searching... (%c)\n", s[i]);
		if ((unsigned char)s[i] == (unsigned char)c)
			nb_occur++;
		if (pos == nb_occur)
		{
			// printf("returning finding result\n");
			return ((char *)&(s[i]));
		}
		i++;
	}
	if ((unsigned char)c == '\0')
	{
		// printf("returning \\0 string\n");
		return ((char *)&(s[i]));
	}
	// printf("returning void string\n");
	return (0);
}

void	free_all(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
