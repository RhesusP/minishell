/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:52:44 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/06/15 17:07:24 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_execve_path(char *cmd, t_env_var *path_var)
{
	int		i;
	char	*temp;
	char	*potential_path;

	if (!path_var || !path_var->values || !path_var->values[0])
		return (0);
	i = 0;
	while (path_var->values[i] != NULL)
	{
		temp = ft_strjoin_nullable(path_var->values[i], "/");
		potential_path = ft_strjoin_nullable(temp, cmd);
		free(temp);
		if (access(potential_path, X_OK) == 0)
			return (potential_path);
		free(potential_path);
		i++;
	}
	return (NULL);
}

void	execute_line(t_word	**word, t_env_var **env, t_env_var **gbl, char *ln)
{
	int			pipes_nbr;
	int			count;
	t_to_free	to_free;

	count = 0;
	pipes_nbr = count_pipes(word);
	to_free.lst = word;
	to_free.env = env;
	to_free.global = gbl;
	to_free.line = ln;
	to_free.tubes = create_tubes(pipes_nbr);
	to_free.command = malloc(sizeof(t_word *));
	if (!to_free.command)
		return ;
	*(to_free.command) = 0;
	while (get_next_cmd(word, &(to_free.command)))
	{
		if (!execute_non_fork_builtin(to_free, pipes_nbr))
			ft_execve(to_free, count, pipes_nbr);
		clear_word_lst(to_free.command);
		count++;
	}
	free_word_lst(to_free.command);
	free_tubes(to_free.tubes);
}
