/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:52:44 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/07/21 13:36:57 by cbernot          ###   ########.fr       */
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

static void	clean_null_args(void)
{
	t_word	*first;
	t_word	*next;

	first = *(g_gbl.command);
	if (first && first->word && first->word[0] == '\0')
	{
		next = first->next;
		if (next)
		{
			*(g_gbl.command) = next;
			if (first->type == CMD && next->type == ARG)
				next->type = CMD;
		}
		else
			*g_gbl.command = 0;
	}
	else if (first && first->type == ARG && ft_strlen(first->word) > 0)
		first->type = CMD;
}

void	wait_child_processes(t_to_free *f, int nb_pipes)
{
	int	i;
	int	status;
	int	ret;

	i = 0;
	while (i <= nb_pipes)
	{
		status = 0;
		ret = 0;
		if (f && f->pids && f->pids[i] && f->pids[i] != -999)
		{
			waitpid(f->pids[i], &status, 0);
			if (WIFEXITED(status))
				g_gbl.status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				get_sig_event(status);
		}
		i++;
	}
	signal_handler(1);
	unlink_he_files(f, nb_pipes);
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

void	execute_line(t_word	**word, t_env_var **env, char *line)
{
	int			i;
	int			nb_pipes;
	static int	idx = 1;

	nb_pipes = count_pipes(word);
	g_gbl.nb_pipes = nb_pipes;
	i = -1;
	init_to_free(nb_pipes, word, line);
	g_gbl.env = env;
	while (get_next_cmd(word, &g_gbl.command))
	{
		g_gbl.he_files[++i] = generate_filename(idx++);
		clean_null_args();
		if (*g_gbl.command)
		{
			if (execute_non_fork_builtin(nb_pipes))
				g_gbl.pids[i] = -999;
			else
				ft_execve(&g_gbl, get_env_custom("PATH", *env), i, nb_pipes);
		}
		clear_word_lst(g_gbl.command);
	}
	wait_child_processes(&g_gbl, nb_pipes);
	free(g_gbl.pids);
	free(g_gbl.command);
}
