/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 08:17:53 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/19 16:48:18 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	execute_cmd(t_to_free *to_free, char **full_cmd, t_env_var *path)
{
	char	*exec_path;
	char	**str_env;

	exec_path = get_execve_path(full_cmd[0], path);
	if (!exec_path)
		check_cmd_err(to_free, full_cmd);
	str_env = env_to_tab(*to_free->env);
	if (full_cmd[0] && !exec_path)
	{
		if (execve(full_cmd[0], full_cmd, str_env) == -1)
			handle_execve_fail(to_free, full_cmd, str_env);
	}
	else
	{
		if (execve(exec_path, full_cmd, str_env) == -1)
		{
			free(exec_path);
			handle_execve_fail(to_free, full_cmd, str_env);
		}
	}
	free_all(full_cmd);
	free_all(str_env);
	free_and_exit(*to_free, 1, EXIT_SUCCESS);
}

void	do_exec_redir(t_to_free *to_free, char ***full_cmd, int i)
{
	t_redir	**redir;
	char	**temp;

	redir = get_redir(to_free->command);
	if (redir)
	{
		temp = handle_redirection(redir, *full_cmd, to_free->he_files[i]);
		if (!temp)
		{
			free_redir(redir);
			free_all(*full_cmd);
			free_and_exit(*to_free, 1, g_status);
		}
		*full_cmd = copy_string_array(temp);
		free_all(temp);
	}
	free_redir(redir);
}

void	child_process(t_to_free *f, t_env_var *path, int nb_pipes, int i)
{
	char	**full_cmd;
	int		j;

	signal_handler(2);
	full_cmd = lst_to_string(f->command);
	do_exec_redir(f, &full_cmd, i);
	if (execute_builtin(f->command, f->env, nb_pipes))
	{
		j = 0;
		while (j < nb_pipes + 2)
		{
			free(f->he_files[j]);
			j++;
		}
		free(f->he_files);
		free_all(full_cmd);
		free_and_exit(*f, 1, g_status);
	}
	execute_cmd(f, full_cmd, path);
}

static void	close_pipes(int index, int nb_pipes, int *input_fd, int pipe_fd[2])
{
	if (index != 0)
		close(*input_fd);
	if (index != nb_pipes)
	{
		close(pipe_fd[1]);
		*input_fd = pipe_fd[0];
	}
}

void	ft_execve(t_to_free *to_free, t_env_var *path, int index, int nb_pipes)
{
	static int	input_fd = STDIN_FILENO;
	int			pipe_fd[2];
	int			pid;

	if (index != nb_pipes)
		pipe(pipe_fd);
	pid = fork();
	if (pid > 0)
		to_free->pids[index] = pid;
	if (pid == 0)
	{
		if (index != 0)
		{
			dup2(input_fd, STDIN_FILENO);
			close(input_fd);
		}
		if (index != nb_pipes)
		{
			dup2(pipe_fd[1], STDOUT_FILENO);
			close(pipe_fd[0]);
			close(pipe_fd[1]);
		}
		child_process(to_free, path, nb_pipes, index);
	}
	close_pipes(index, nb_pipes, &input_fd, pipe_fd);
}
