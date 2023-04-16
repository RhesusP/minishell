/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:48:39 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/04/14 14:46:39 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/exec.h"

t_env_var	*is_var_exists(t_env_var *env, char *search)
{
	t_env_var	*current;

	if (!env)
		return (0);
	current = env;
	while (current)
	{
		if (ft_strcmp(current->key, search) == 0)
			return (current);
		current = current->next;
	}
	return (0);
}

void	ft_export(t_word **lst, t_env_var *env)
{
	// TODO export alone
	display_words(lst);
	t_word	*current;
	t_env_var	*var;

	if (!*lst)
		return ;
	current = *lst;
	while (current && current->type != ARG)
		current = current->next;
	while (current && current->type == ARG)
	{
		var = is_var_exists(env, get_var_key(current->word));
		if (!var)
			add_back_env_var(&env, create_env_var(current->word));
		else
		{
			free(var->values);
			var->values = get_var_values(current->word);
		}
		current = current->next;
	}
}
