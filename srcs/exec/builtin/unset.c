/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 13:00:37 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/05/10 22:30:02 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_unset(t_word **lst, t_env_var **env, t_env_var **global)
{
	t_word		*current;

	if (!*lst)
		return ;
	current = *lst;
	while (current && current->type != ARG)
		current = current->next;
	while (current && current->type == ARG)
	{
		delete_existing_key(env, current->word);
		delete_existing_key(global, current->word);
		current = current->next;
	}
}
