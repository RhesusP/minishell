/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:19:23 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/05/12 14:52:10 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_getcwd()
{
	char 	*pwd;
	int		size;

	size = 256;
	pwd = malloc(sizeof(char) * size);
	while (!getcwd(pwd, 256))
		size += 256;
	return (pwd);
}

void	ft_pwd()
{
	char 	*pwd;
	
	pwd = ft_getcwd();
	printf("%s\n", pwd);
	free(pwd);	
}
