/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 08:17:53 by cbernot           #+#    #+#             */
/*   Updated: 2023/06/16 11:42:58 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	parent_process(t_to_free f, int pid, int count, t_redir **redir)
{
	int	status;

	status = 0;
	if (count > 0)
	{
		close(f.tubes[count - 1][0]);
		close(f.tubes[count - 1][1]);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_status = WEXITSTATUS(status);
	free_redir(redir);
}

static void	link_processes(t_to_free to_free, int count, int nb_pipes)
{
	if (count > 0)
	{
		dup2(to_free.tubes[count - 1][0], STDIN_FILENO);
		close(to_free.tubes[count - 1][0]);
		close(to_free.tubes[count - 1][1]);
	}
	if (count < nb_pipes)
	{
		dup2(to_free.tubes[count][1], STDOUT_FILENO);
		close(to_free.tubes[count][0]);
		close(to_free.tubes[count][1]);
	}
}

static void	exec_cmd(t_to_free f, char **full_cmd, char **str_env, char *exec)
{
	if (full_cmd[0] && !exec)
	{
		if (execve(full_cmd[0], full_cmd, str_env) == -1)
		{
			ft_putstr_fd(full_cmd[0], 2);
			ft_putendl_fd(": command not found", 2);
			g_status = 127;
		}
	}
	else
	{
		if (execve(exec, full_cmd, str_env) == -1)
		{
			ft_putstr_fd(full_cmd[0], 2);
			ft_putendl_fd(": command not found", 2);
			g_status = 127;
			free(exec);
		}
	}
	free_all(str_env);
	if (g_status == 127)
		free_and_exit(f, 1, 127);
	else
		free_and_exit(f, 1, EXIT_SUCCESS);
}

static void	child_process(t_to_free f, int count, int n_pp, t_redir **redir)
{
	char	**full_cmd;
	char	**temp;
	char	**str_env;
	char	*exec_path;

	link_processes(f, count, n_pp);
	full_cmd = lst_to_string(f.command);
	if (redir)
	{
		temp = handle_redirection(redir, full_cmd);
		full_cmd = copy_string_array(temp);
		free_all(temp);
	}
	free_redir(redir);
	if (!full_cmd[0])
		free_and_exit(f, 1, 0);
	if (execute_builtin(f.command, f.env, n_pp))
		free_and_exit(f, 1, EXIT_SUCCESS);
	exec_path = get_execve_path(full_cmd[0], get_env_custom("PATH", *f.env));
	str_env = env_to_tab(*(f.env));
	exec_cmd(f, full_cmd, str_env, exec_path);
}

void	ft_execve(t_to_free to_free, int count, int nb_pipes)
{
	char	**full_cmd;
	int		pid;
	t_redir	**redir;

	pid = fork();
	redir = get_redir(to_free.command);
	if (pid == -1)
		perror("failed to fork\n");
	if (pid > 0)
		parent_process(to_free, pid, count, redir);
	if (pid == 0)
		child_process(to_free, count, nb_pipes, redir);
}
