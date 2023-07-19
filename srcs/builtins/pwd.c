/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmeen <svanmeen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:19:23 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/07/19 13:43:23 by svanmeen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/// @brief Get pwd
/// @return pwd
char	*ft_getcwd(void)
{
	char	*pwd;
	int		size;
	int		nb;

	nb = 0;
	size = 256;
	pwd = malloc(sizeof(char) * size);
	while (!getcwd(pwd, 256))
		size += 256;
	return (pwd);
}

/// @brief builtin pwd and print it
void	ft_pwd(void)
{
	char	*pwd;

	pwd = ft_getcwd();
	printf("%s\n", pwd);
	free(pwd);
}
