/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_redo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:26:16 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/05 16:02:38 by cbernot          ###   ########.fr       */
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

void	create_pipes(t_exec *exec)
{
	int	i;

	exec->pipes = malloc(sizeof(int) * 2 * exec->nb_pipes);
	if (!exec->pipes)
		exit(EXIT_FAILURE);	//TODO secure
	i = 0;
	while (i < exec->nb_pipes)
	{
		if (pipe(exec->pipes + 2 * i) == -1)
			exit(EXIT_FAILURE);	//TODO secure
		i++;
	}
}

void	close_pipes(t_exec *exec)
{
	int	i;

	i = 0;
	while (i < exec->nb_pipes)
	{
		close(exec->pipes[i]);
		i++;
	}
}

void	child_process2(t_exec *exec, t_word **lst, t_env_var *path, int count, int nb_pipes, t_env_var **env, t_env_var **global, t_word **word)
{
	// exec->pid = fork();
	// if (exec->pid == 0)
	// {
	// 	if (exec->index == 0)
			
	// }
	static int input_fd = STDIN_FILENO;
	int pipe_fd[2];
	if (exec->index != exec->nb_pipes)
		pipe(pipe_fd);
	int pid = fork();
	if (pid == 0)
	{
		// processus fils
		if (exec->index != 0)
		{
			dup2(input_fd, STDIN_FILENO);
			close(input_fd);
		}
		if (exec->index != exec->nb_pipes)
		{
			dup2(pipe_fd[1], STDOUT_FILENO);
			close(pipe_fd[0]);
			close(pipe_fd[1]);
		}
		char **full_cmd = lst_to_string(lst);
		
		// if (execute_builtin(lst, env, nb_pipes))
		// {
		// 	exit(EXIT_SUCCESS);
		// }

		char *exec_path = get_execve_path(full_cmd[0], path);
		
		char	**str_env;
		str_env = env_to_tab(*env);

		if (full_cmd[0] && !exec_path)
		{
			// printf("CAS 1\n");
			if (execve(full_cmd[0], full_cmd, str_env) == -1)
			{
				ft_putstr_fd(full_cmd[0], 2);
				ft_putendl_fd(": command not found", 2);
				g_status = 127;
			}
		}
		else
		{
			if (execve(exec_path, full_cmd, str_env) == -1)
			{
				
				ft_putstr_fd(full_cmd[0], 2);
				ft_putendl_fd(": command not found", 2);
				g_status = 127;
				free(exec_path);
			}
		}
	}
	if (exec->index != 0)
		close(input_fd);
	if (exec->index != exec->nb_pipes)
	{
		close(pipe_fd[1]);
		input_fd = pipe_fd[0];
	}
}

void	execute_line(t_word	**word, t_env_var **env, t_env_var **global, char *line)
{

	t_exec	exec;
	t_env_var *path;
	t_word		**cmd;

	// Compter le nombre de pipes / commandes
	exec.nb_pipes = count_pipes(word);
	// creer les pipes
	// create_pipes(&exec);
	exec.index = 0;
	cmd = malloc(sizeof(t_word *));
	if (!cmd)		//TODO catch error
		return ;
	*cmd = 0;
	// Lancer les processus
	while (get_next_cmd(word, &cmd))
	{		
		path = get_env_custom("PATH", *env);
		child_process2(&exec, cmd, path, exec.index, exec.nb_pipes, env, global, word);
		exec.index++;
		clear_word_lst(cmd);
	}
	int i = 0;
	while (i <= exec.nb_pipes)
	{
		wait(NULL);
		i++;
	}
	// fermer les pipes
	// close_pipes(&exec);
	// attendre la fin des processus
	waitpid(-1, NULL, 0);
}
