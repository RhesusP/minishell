/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 08:37:25 by cbernot           #+#    #+#             */
/*   Updated: 2023/06/21 19:11:54 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

char	*get_quoted(char *str, t_env_var **env, t_env_var **global)
{
	int		size;
	char	**tab;
	char	*res;
	char	*temp;
	
	size = get_nb_quoted_words(str);
	tab = fill_quoted_tab(str, size);
	int i = 0;
	while (i < size)
	{
		if (tab[i][0] != '\'')
			tab[i] = get_vars(tab[i], env, global);
		if (tab[i][0] == '\'' || tab[i][0] == '"')
		{
			temp = remove_quotes(tab[i]);
			free(tab[i]);
			tab[i] = temp;
		}
		i++;
	}
	res = join_tab(tab, size);
	i = 0;	
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (res);
}

void	var_expansion(t_word **words_lst, t_env_var **global_vars, t_env_var **env_vars)
{
	t_word	*current;
	int		quoted_case;
	char	*temp;

	if (!words_lst || !*words_lst)
		return ;
	current = *words_lst;
	while (current)
	{
		temp = get_quoted(current->word, env_vars, global_vars);
		free(current->word);
		current->word = temp;
		current = current->next;
	}
}
