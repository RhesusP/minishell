/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:39:26 by cbernot           #+#    #+#             */
/*   Updated: 2023/02/26 00:40:52 by cbernot          ###   ########.fr       */
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