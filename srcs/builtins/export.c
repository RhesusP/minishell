/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:48:39 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/06/16 11:50:34 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	create_export_var(t_word *current, t_env_var **env)
{
	char		*key;
	t_env_var	*new;
	int			i;

	key = get_var_key(current->word);
	if (is_already_here(env, key))
	{
		new = get_env_custom(key, *env);
		i = 0;
		while (new->values[i])
		{
			free(new->values[i]);
			i++;
		}
		free(new->values);
		new->values = get_var_values(current->word);
	}
	else
	{
		new = create_env_var(current->word);
		add_back_env_var(env, new);
	}
	free(key);
}

static void	export_vars(t_word **lst, t_env_var **env)
{
	t_word	*current;
	int		status;

	if (!*lst || !env ||!*env)
		return ;
	current = *lst;
	while (current && current->type != ARG)
		current = current->next;
	while (current && current->type == ARG)
	{
		status = is_export_syntax_valid(current->word);
		if (status == 1)
			create_export_var(current, env);
		else if (status == 0)
		{
			ft_putstr_fd("export '", 2);
			ft_putstr_fd(current->word, 2);
			ft_putendl_fd("': not a valid identifier", 2);
		}
		current = current->next;
	}
}

int	get_nb_arg(t_word **lst)
{
	t_word	*current;
	int		nb_arg;

	nb_arg = 0;
	current = *lst;
	while (current && current->type != ARG)
		current = current->next;
	while (current && current->type == ARG)
	{
		nb_arg++;
		current = current->next;
	}
	return (nb_arg);
}

void	ft_export(t_word **lst, t_env_var **e, int forked, int n_pipe)
{
	int		nb_arg;
	t_word	*current;
	int		redir;

	redir = 0;
	nb_arg = 0;
	current = *lst;
	while (current)
	{
		if (type_is_redir(current))
			redir = 1;
		current = current->next;
	}
	nb_arg = get_nb_arg(lst);
	if ((nb_arg == 0 && !forked && n_pipe == 0 && !redir) || \
		(nb_arg == 0 && forked))
		print_export(*e);
	else
	{
		if (!forked)
			export_vars(lst, e);
	}
}
