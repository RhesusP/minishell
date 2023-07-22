/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 11:20:28 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/22 14:50:11 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Print the export syntax of the environment variables.
 * 
 * @param env Environment variables list to print.
 */
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

/**
 * @brief Check if the syntax of the variable to export is valid.
 * 
 * @param str Variable to export.
 * @return int 1 if the syntax is valid, 0 otherwise.
 */
int	is_export_syntax_valid(char *str)
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
