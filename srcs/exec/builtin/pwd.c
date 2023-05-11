/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:19:23 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/05/11 18:03:43 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_pwd(t_env_var *env)
{
	char 	*alt;
	int		size;
	
	size = 256;
	alt = malloc(sizeof(char) * size);
	while (!getcwd(alt, 256))
		size += 256;
	printf("%s\n", alt);
	free(alt);	
}
