/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:19:23 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/07/22 16:52:09 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Get the current working directory.
 * 
 * @return char* 
 */
char	*ft_getcwd(void)
{
	char	*pwd;
	int		size;

	size = 256;
	pwd = malloc(sizeof(char) * size);
	while (!getcwd(pwd, 256))
		size += 256;
	return (pwd);
}

/**
 * @brief Print the current working directory.
 * 
 */
void	ft_pwd(void)
{
	char	*pwd;

	pwd = ft_getcwd();
	printf("%s\n", pwd);
	free(pwd);
}
