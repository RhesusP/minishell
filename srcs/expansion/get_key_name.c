/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_key_name.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 08:57:22 by cbernot           #+#    #+#             */
/*   Updated: 2023/06/16 11:15:58 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

static int	get_pre_name(char *str, char **tab)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '$')
		i++;
	if (i > 0)
		tab[0] = ft_strndup(str, i);
	else
		tab[0] = 0;
	return (i);
}

static void	get_name_post_name(char *str, char **tab, int i, int len)
{
	while (str[len] != '\0' && (str[len] == '_' || str[len] == '?' \
			|| ft_isalnum(str[len])))
		len++;
	tab[1] = ft_strndup(&str[i], len - i);
	if (len < ft_strlen(str) && str[len])
		tab[2] = ft_strdup(&str[len]);
	else
		tab[2] = 0;
}

char	**get_key_name(char *str)
{
	int		len;
	int		i;
	char	**tab;

	tab = malloc(sizeof(char *) * 3);
	if (!tab)
		return (0);
	i = get_pre_name(str, tab);
	len = i + 1;
	if (len < ft_strlen(str))
		get_name_post_name(str, tab, i, len);
	else
	{
		tab[1] = 0;
		tab[2] = 0;
	}
	return (tab);
}
