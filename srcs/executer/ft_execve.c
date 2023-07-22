/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 08:17:53 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/22 13:32:24 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Get the path of the command executable to execute and execute it.
 * 
 * @param f 
 * @param cmd String array of the command to execute.
 * @param path $PATH environment variable.
 * @param nb_pipes Number of pipes in the current command.
 */
static void	execute_cmd(t_to_free *f, char **cmd, t_env_var *path, int nb_pipes)
{
	char	*exec_path;

	exec_path = get_execve_path(cmd[0], path);
	if (!exec_path)
		check_cmd_err(f, cmd, nb_pipes);
	g_gbl.str_env = env_to_tab(*f->env);
	if (cmd[0] && !exec_path)
	{
		if (execve(cmd[0], cmd, g_gbl.str_env) == -1)
			handle_execve_fail(f, cmd, g_gbl.str_env, nb_pipes);
	}
	else
	{
		if (execve(exec_path, cmd, g_gbl.str_env) == -1)
		{
			free(exec_path);
			handle_execve_fail(f, cmd, g_gbl.str_env, nb_pipes);
		}
	}
	free_all(cmd);
	g_gbl.full_cmd = 0;
	free_all(g_gbl.str_env);
	g_gbl.str_env = 0;
	free_and_exit(f, 1, EXIT_SUCCESS, 1);
}

/**
 * @brief Child process.
 * @details Define a signal handler for SIGINT, handle redirections,
 * execute the command and exit the child with the correct exit status.
 * @param f 
 * @param path $PATH environment variable.
 * @param nb_pipes Number of pipes in the current command.
 * @param i Index of the current sub-command.
 */
static void	child_process(t_to_free *f, t_env_var *path, int nb_pipes, int i)
{
	int		j;

	g_gbl.in_hd = 0;
	signal_handler(2);
	g_gbl.full_cmd = lst_to_string(f->command);
	do_exec_redir(f, &g_gbl.full_cmd, i);
	if (execute_builtin(f->command, f->env, nb_pipes))
	{
		j = 0;
		while (j < nb_pipes + 2)
		{
			free(f->he_files[j]);
			j++;
		}
		free(f->he_files);
		free_all(g_gbl.full_cmd);
		g_gbl.full_cmd = 0;
		free_and_exit(f, 1, g_gbl.status, 0);
	}
	execute_cmd(f, g_gbl.full_cmd, path, nb_pipes);
}

/**
 * @brief Close all pipes.
 * 
 * @param index Index of the current sub-command.
 * @param nb_pipes Number of pipes in the current command.
 * @param input_fd input file descriptor
 * @param pipe_fd tube
 */
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

/**
 * @brief Parent process.
 * @details Ignores the SIGINT signal and stores the pid of the child process
 * @param to_free 
 * @param pid Child process pid.
 * @param index Index of the current command.
 */
static void	parent_process(t_to_free *to_free, int pid, int index)
{
	signal(SIGINT, SIG_IGN);
	to_free->pids[index] = pid;
}

/**
 * @brief Execute the command.
 * 
 * @param to_free 
 * @param path 
 * @param index Index of the current sub-command.
 * @param nb_pipes Number of pipes in the current command.
 */
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
