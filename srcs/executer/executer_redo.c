/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_redo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:26:16 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/13 18:27:55 by cbernot          ###   ########.fr       */
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

void	child_process2(t_to_free *to_free, t_env_var *path, int index, int nb_pipes)
{
	static int input_fd = STDIN_FILENO;
	
	int pipe_fd[2];
	if (index != nb_pipes)
		pipe(pipe_fd);
	int pid = fork();
	if (pid > 0)
		to_free->pids[index] = pid;
	if (pid == 0)
	{
		// processus fils
		t_redir	**redir;
		redir = get_redir(to_free->command);
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
		char **full_cmd = lst_to_string(to_free->command);
		char	**temp;
		if (redir)
		{
			temp = handle_redirection(redir, full_cmd);
			if (!temp)
				free_and_exit(*to_free, 1, g_status);
			full_cmd = copy_string_array(temp);
			free_all(temp);
		}
		free_redir(redir);
		if (execute_builtin(to_free->command, to_free->env, nb_pipes))
		{
			free_all(full_cmd);
			free_and_exit(*to_free, 1, g_status);
		}
		char *exec_path = get_execve_path(full_cmd[0], path);
		if (!exec_path)
		{
			struct stat	path;
			if (stat(full_cmd[0], &path) == 0)
			{
				if (S_ISDIR(path.st_mode))
				{
					// printf("C'est un dossier\n");
					ft_putstr_fd(full_cmd[0], STDERR_FILENO);
					ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
					g_status = 126;
					free_and_exit(*to_free, 1, g_status);
				}
				else
				{
					if (access(full_cmd[0], X_OK) != 0)
					{
						ft_putstr_fd(full_cmd[0], STDERR_FILENO);
						ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
						g_status = 126;
						free_and_exit(*to_free, 1, g_status);
					}
				}	
			}
			else
			{
				if (ft_strncmp(full_cmd[0], "./", 2) == 0)
				{
					ft_putstr_fd(full_cmd[0], STDERR_FILENO);
					ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
					g_status = 127;
					free_and_exit(*to_free, 1, g_status);
				}
			}
		}
		
		char	**str_env;
		str_env = env_to_tab(*to_free->env);

		if (full_cmd[0] && !exec_path)
		{
			// printf("CAS 1\n");
			if (execve(full_cmd[0], full_cmd, str_env) == -1)
			{
				ft_putstr_fd(full_cmd[0], STDERR_FILENO);
				ft_putstr_fd(": command not found\n", STDERR_FILENO);
				g_status = 127;
				free_all(full_cmd);
				free_all(str_env);
				free_and_exit(*to_free, 1, g_status);
			}
		}
		else
		{
			if (execve(exec_path, full_cmd, str_env) == -1)
			{
				// display_errmsg();
				free(exec_path);
				ft_putstr_fd(full_cmd[0], STDERR_FILENO);
				ft_putstr_fd(": command not found\n", STDERR_FILENO);
				g_status = 127;
				free_all(full_cmd);
				free_all(str_env);
				free_and_exit(*to_free, 1, g_status);
		}
		}
		free_all(str_env);
		free_and_exit(*to_free, 1, EXIT_SUCCESS);
	}
	if (index != 0)
		close(input_fd);
	if (index != nb_pipes)
	{
		close(pipe_fd[1]);
		input_fd = pipe_fd[0];
	}
}

void	execute_line(t_word	**word, t_env_var **env, t_env_var **global, char *line)
{
	t_env_var *path;
	t_to_free	to_free;
	int			index;
	int			nb_pipes;

	// Compter le nombre de pipes / commandes
	nb_pipes = count_pipes(word);
	index = 0;
	
	to_free.pids = malloc(sizeof(int) * (nb_pipes + 1));
	if (!to_free.pids)
		return ;
	to_free.lst = word;
	to_free.env = env;
	to_free.global = global;
	to_free.line = line;
	to_free.command = malloc(sizeof(t_word *));
	if (!to_free.command)
		return ;
	*(to_free.command) = 0;

	// Lancer les processus
	while (get_next_cmd(word, &to_free.command))
	{		
		path = get_env_custom("PATH", *env);
		t_word	*first;
		t_word	*next;
		first = *(to_free.command);
		if (first && first->word && first->word[0] == '\0')
		{
			next = first->next;
			if (next)
			{
				*(to_free.command) = next;
				if (first->type == CMD && next->type == ARG)
					next->type = CMD;
			}
			else
			{
				*to_free.command = 0;
			}
		}
		if (*to_free.command)
		{
			if (execute_non_fork_builtin(to_free, nb_pipes))
				to_free.pids[index] = -999;
			else
				child_process2(&to_free, path, index, nb_pipes);
		}
		index++;
		clear_word_lst(to_free.command);
	}
	int i = 0;
	int status;
	status = 0;
	while (i <= nb_pipes)
	{
		if (to_free.pids[i] != -999)
		{
			waitpid(to_free.pids[i], &status, 0);
			if (WIFEXITED(status))
			{
				g_status = WEXITSTATUS(status);
			}
		}
		i++;
	}
	// waitpid(-1, NULL, 0);
	free(to_free.pids);
	free(to_free.command);
}
