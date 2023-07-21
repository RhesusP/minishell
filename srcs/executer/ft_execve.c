/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 08:17:53 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/21 09:49:18 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	execute_cmd(t_to_free *f, char **cmd, t_env_var *path, int nb_pipes)
{
	char	*exec_path;
	char	**str_env;

	exec_path = get_execve_path(cmd[0], path);
	if (!exec_path)
		check_cmd_err(f, cmd, nb_pipes);
	str_env = env_to_tab(*f->env);
	if (cmd[0] && !exec_path)
	{
		if (execve(cmd[0], cmd, str_env) == -1)
			handle_execve_fail(f, cmd, str_env, nb_pipes);
	}
	else
	{
		if (execve(exec_path, cmd, str_env) == -1)
		{
			free(exec_path);
			handle_execve_fail(f, cmd, str_env, nb_pipes);
		}
	}
	free_all(cmd);
	free_all(str_env);
	free_and_exit(*f, 1, EXIT_SUCCESS);
}

static void	child_process(t_to_free *f, t_env_var *path, int nb_pipes, int i)
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
	execute_cmd(f, full_cmd, path, nb_pipes);
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

static void	parent_process(t_to_free *to_free, int pid, int index)
{
	signal(SIGINT, SIG_IGN);
	to_free->pids[index] = pid;
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
		parent_process(to_free, pid, index);
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
