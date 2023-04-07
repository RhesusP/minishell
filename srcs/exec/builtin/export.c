/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:48:39 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/04/07 12:20:31 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/exec.h"

void	ft_export(t_word **lst, t_env_var *env)
{
	display_words(lst);
}





// /**
// *	@brief check that the variable we want to export is like TYPE=something
// **/
// static int	exportable_variable(char *new_var)
// {
// 	int	i;

// 	i = 0;
// 	while (new_var[i])
// 	{
// 		if (new_var[i] == '=')
// 			return (SUCCESS);
// 		i++;
// 	}
// 	return (FAILURE);
// }

// /**
//  * @brief	Extract the key from the new_var --> [KEY]=VALUES
// **/
// static	char	*get_new_var_key(char *new_var)
// {
// 	char *new_var_key;
// 	int	i;

// 	i = 0;
// 	while (new_var[i] != '=')
// 		i++;
// 	new_var_key = calloc(i, sizeof(char));
// 	i = 0;
// 	while (new_var[i] != '=')
// 	{
// 		new_var_key[i] = new_var[i];
// 		i++;
// 	}
// 	return (new_var_key);
// }

// static int	char_are_equals(char *s1, char *s2)
// {
// 	int	i;

// 	i = 0;
// 	if (ft_strlen(s1) != ft_strlen(s2))
// 		return (FAILURE);
// 	while (s1[i] && s2[i])
// 	{
// 		if (s1[i] != s2[i])
// 			return (FAILURE);
// 		i++;
// 	}
// 	return (SUCCESS);
// }

// /**
//  * @brief check that the variable we want to export doesn't already exists //
//  *	If it exists, unset it so we can then add it to the back of the list
// **/
// static int	variable_already_exists(t_env_var *env_var, char *new_var)
// {
// 	char	*new_var_key;

// 	new_var_key = get_new_var_key(new_var);
// 	printf("%s\n", new_var_key);
// 	printf("%s\n", env_var->key);
// 	int i = 0;
// 	while (env_var)
// 	{
// 		if (char_are_equals(env_var->key, new_var_key) == SUCCESS)
// 		{
// 			printf("key is found %s\n", env_var->key);
// 			exec_unset(env_var, env_var->key);
// 			free(new_var_key);
// 			return (SUCCESS);
// 		}
// 		env_var = env_var->next;
// 	}
// 	free(new_var_key);
// 	return (FAILURE);
// }

// void	exec_export(t_env_var *env_var, char *new_var)
// {
// 	if (exportable_variable(new_var) == SUCCESS)
// 	{
// 		variable_already_exists(env_var, new_var);
// 		env_var_add_back(&env_var, env_var_new(new_var));
// 	}
// }
