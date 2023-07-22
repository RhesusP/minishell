/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:39:26 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/21 16:01:47 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

/**
 * @brief Allocates sufficient memory for a copy of size chars of the string s1, 
 * does the copy, and returns a pointer to it.  The pointer may subsequently be
 * used as an argument to the function free(3).
 * 
 * @param s1 
 * @param size
 * @return If successfull, it returns a pointer to allocated memory. If there is
 * an error, it returns a NULL pointer.
 */
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

/**
 * @brief Lexicographically compare the null-terminated strings s1 and s2 
 * 
 * @param s1 
 * @param s2 
 * @param n 
 * @return An integer greater than, equal to, or less than 0, according as the
 * string s1 is greater than, equal to, or less than the string s2.
 */
int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (ft_strlen(s1) != ft_strlen(s2))
		return (FAILURE);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

/**
 * @brief Free all the strings in the array and the array itself
 * 
 * @param str The array of strings to free
 */
void	free_all(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

/**
 * @brief ft_strjoin but accepts NULL strings.
 * 
 * @param s1 
 * @param s2 
 * @return The concatenation of the two strings.
 */
char	*ft_strjoin_nullable(char *s1, char *s2)
{
	char	*res;

	if (!s1 && !s2)
	{
		res = malloc(sizeof(char));
		if (!res)
			return (NULL);
		res[0] = '\0';
		return (res);
	}
	else if (s1 && !s2)
		return (ft_strdup(s1));
	else if (!s1 && s2)
		return (ft_strdup(s2));
	else
		return (ft_strjoin(s1, s2));
}

/**
 * @brief Check if the character is a space
 * 
 * @param c 
 * @return 1 if it is a space, 0 otherwise
 */
int	ft_isspace(const char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}
