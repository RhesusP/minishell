/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 11:20:28 by cbernot           #+#    #+#             */
/*   Updated: 2023/06/15 11:22:41 by cbernot          ###   ########.fr       */
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
