/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:19:23 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/03/08 12:22:10 by tbarde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/exec.h"

void	exec_pwd(t_env_var *env_var)
{
	t_env_var	*pwd;
	pwd = get_env_custom("PWD", env_var);
	printf("%s\n", pwd->values[0]);
}
