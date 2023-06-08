/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:48:39 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/05/31 11:49:58 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_export(t_env_var *env)
{
	t_env_var	*current;
	int			i;

	if (!env)
		return ;
	current = env;
	while (current)
	{
		if (ft_strcmp("_", current->key) != 0)
		{
			printf("declare -x %s=\"", current->key);
			i = 0;
			while (current->values[i])
			{
				printf("%s", current->values[i]);
				if (current->values[i + 1])
					printf(":");
				i++;
			}
			printf("\"\n");
		}
		current = current->next;
	}
}

// Return 0 for bad syntax and -1 for nothing to do
int	is_syntax_valid(char *str)
{
	int	i;
	int	is_valid;

	is_valid = 0;
	i = 0;
	if (ft_isdigit(str[0]))
		return (0);
	while (str[i] != '\0' && (ft_isalnum(str[i]) || str[i] == '_'))
	{
		is_valid = 1;
		i++;
	}
	if (str[i] == '\0')
		return (-1);
	if (str[i] == '=' && is_valid)
		is_valid = 1;
	else
		is_valid = 0;
	return (is_valid);
}

void	create_export_var(t_word *current, t_env_var **env)
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

void	export_vars(t_word **lst, t_env_var **env)
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
		status = is_syntax_valid(current->word);
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

void	ft_export(t_word **lst, t_env_var **env, int forked, int nb_pipes)
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
	current = *lst;
	while (current && current->type != ARG)
		current = current->next;
	while (current && current->type == ARG)
	{
		nb_arg++;
		current = current->next;
	}
	if ((nb_arg == 0 && !forked && nb_pipes == 0 && !redir) || (nb_arg == 0 && forked))
		print_export(*env);
	else
	{
		if (!forked)
			export_vars(lst, env);
	}
}
