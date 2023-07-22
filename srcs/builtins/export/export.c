/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:48:39 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/07/22 18:24:23 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/**
 * @brief Add the new variable to the environment variables list.
 * 
 * @param current Variable to add in the environment.
 * @param env Environment variables list.
 */
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

/**
 * @brief Check if the syntax of the variable to export is valid.
 * 
 * @param lst Sub-command to execute.
 * @param env Environment variables list.
 */
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
		{
			create_export_var(current, env);
			g_gbl.status = 0;
		}
		else if (status == 0)
		{
			g_gbl.status = 1;
			ft_putstr_fd("export '", 2);
			ft_putstr_fd(current->word, 2);
			ft_putendl_fd("': not a valid identifier", 2);
		}
		current = current->next;
	}
}

/**
 * @brief Get the number of arguments in the command.
 * 
 * @param lst Sub-command to execute.
 * @return int Number of arguments.
 */
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

int	have_redir_in_cmd(t_word **lst)
{
	t_word	*current;
	int		redir;

	redir = 0;
	current = *lst;
	while (current)
	{
		if (type_is_redir(current))
			redir = 1;
		current = current->next;
	}
	return (redir);
}

/**
 * @brief Print the environment variables list or add a new variable to it.
 * @details If the command have no argument, it prints the environment variables.
 * @param lst Sub-command to execute.
 * @param e Environment variables list.
 * @param forked Boolean to know if the command is executed in a forked process.
 * @param n_pipe Number of pipes in the current command.
 */
void	ft_export(t_word **lst, t_env_var **e, int forked, int n_pipe)
{
	int		nb_arg;
	int		redir;

	redir = have_redir_in_cmd(lst);
	nb_arg = get_nb_arg(lst);
	if (nb_arg == 0 && !forked && n_pipe == 0 && !redir)
	{
		g_gbl.already_e = 1;
		print_export(*e);
	}
	else if (nb_arg == 0 && forked && !g_gbl.already_e)
	{
		g_gbl.already_e = 0;
		print_export(*e);
	}
	else
	{
		if (!forked)
			export_vars(lst, e);
	}
}
