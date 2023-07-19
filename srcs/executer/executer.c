/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:52:44 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/07/19 16:44:43 by cbernot          ###   ########.fr       */
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

void	clean_null_args(t_to_free *to_free)
{
	t_word	*first;
	t_word	*next;

	first = *(to_free->command);
	if (first && first->word && first->word[0] == '\0')
	{
		next = first->next;
		if (next)
		{
			*(to_free->command) = next;
			if (first->type == CMD && next->type == ARG)
				next->type = CMD;
		}
		else
			*to_free->command = 0;
	}
}

void	wait_child_processes(t_to_free *to_free, int nb_pipes)
{
	int	i;
	int	status;
	int	ret;

	i = 0;
	status = 0;
	while (i <= nb_pipes)
	{
		ret = 0;
		if (to_free->pids[i] != -999)
		{
			waitpid(to_free->pids[i], &status, 0);
			if (WIFEXITED(status))
				g_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				if (status == 131)
					printf("Quit (core dumped)\n");
			}
		}
		i++;
	}
	unlink_he_files(to_free, nb_pipes);
}

char	*generate_filename(int index)
{
	char	*itoa_ret;
	char	*res;

	itoa_ret = ft_itoa(index);
	res = ft_strjoin(".tmp", itoa_ret);
	free(itoa_ret);
	return (res);
}

void	execute_line(t_word	**word, t_env_var **env, t_env_var **g, char *line)
{
	t_to_free	to_free;
	int			i;
	int			nb_pipes;
	static int	idx = 1;

	nb_pipes = count_pipes(word);
	i = -1;
	init_to_free(&to_free, nb_pipes, word, line);
	init_to_free_vars(&to_free, env, g);
	while (get_next_cmd(word, &to_free.command))
	{
		to_free.he_files[++i] = generate_filename(idx++);
		clean_null_args(&to_free);
		if (*to_free.command)
		{
			if (execute_non_fork_builtin(to_free, nb_pipes))
				to_free.pids[i] = -999;
			else
				ft_execve(&to_free, get_env_custom("PATH", *env), i, nb_pipes);
		}
		clear_word_lst(to_free.command);
	}
	wait_child_processes(&to_free, nb_pipes);
	free(to_free.pids);
	free(to_free.command);
}
