/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:52:44 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/06/14 19:36:41 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


/**
*	@brief Get the command with args from the parser into a char **
*	Then we'll be able to pass the full command to execve()
**/
char	**lst_to_string(t_word **lst)
{
	char	**tab;
	int		len;
	t_word	*current;
	int		i;

	i = 0;
	len = get_exec_len(lst);
	tab = malloc(sizeof(t_word *) * (len + 1));
	if (!tab)
		return (0);		//TODO better error handling 
	current = *lst;
	while (current && current->type != CMD && current->type != ARG)
		current = current->next;
	while (current && i < len)
	{
		tab[i] = ft_strdup(current->word);
		current = current->next;
		i++;
	}
	tab[i] = 0;
	return (tab);
}

char	*get_execve_path(char *cmd, t_env_var *path_var)
{
	int		i;
	char	*temp;
	char	*potential_path;

	if (!path_var || !path_var->values || !path_var->values[0])	//TODO check error
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

char	**copy_string_array(char **tab)
{
	int	len;
	int	i;
	char	**res;

	if (!tab)
		return (0);
	len = 0;
	while (tab[len])
		len++;
	res = malloc(sizeof(char *) * (len + 1));
	if (!res)
		return (0);
	i = 0;
	while (tab[i] != 0)
	{
		res[i] = ft_strdup(tab[i]);
		i++;
	}
	res[i] = 0;
	return (res);
}

void	ft_execve(t_to_free to_free, t_env_var *path, int count, int nb_pipes)
{
	char		*exec_path;
	char		**full_cmd;
	int			pid;
	t_redir		**redir;
	int			status;

	status = 0;
	pid = fork();
	redir = get_redir(to_free.command);
	// display_redirs(redir);
	if (pid == -1)
		perror("failed to fork\n");
	if (pid > 0)		//parent process
	{
		if (count > 0)
		{
			close(to_free.tubes[count - 1][0]);
			close(to_free.tubes[count - 1][1]);
		}
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			g_status = WEXITSTATUS(status);
		}
		free_redir(redir);
	}
	if (pid == 0)		//child process
	{
		if (count > 0)
		{
			dup2(to_free.tubes[count - 1][0], STDIN_FILENO);	//duplique la sortie du précedent sur l'entree de l'actuel
			close(to_free.tubes[count - 1][0]);					//ferme l'entrée / sortie du précédent
			close(to_free.tubes[count - 1][1]);
		}
		if (count < nb_pipes)
		{
			dup2(to_free.tubes[count][1], STDOUT_FILENO);	//duplique pour le suivant
			close(to_free.tubes[count][0]);
			close(to_free.tubes[count][1]);
		}
		full_cmd = lst_to_string(to_free.command);
		char	**temp;
		if (redir)
		{
			temp = handle_redirection(redir, full_cmd);
			full_cmd = copy_string_array(temp);
			free_all(temp);
		}
		free_redir(redir);
		if (!full_cmd[0])
			free_and_exit(to_free, 0);
		if (execute_builtin(to_free.command, to_free.env, nb_pipes))
			free_and_exit(to_free, EXIT_SUCCESS);
	
		exec_path = get_execve_path(full_cmd[0], path);
		// printf("exec path: %s\n", exec_path);
		
		char	**str_env;
		str_env = env_to_tab(*(to_free.env));

		if (full_cmd[0] && !exec_path)
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
			if (execve(exec_path, full_cmd, str_env) == -1)
			{
				
				ft_putstr_fd(full_cmd[0], 2);
				ft_putendl_fd(": command not found", 2);
				g_status = 127;
				free(exec_path);
			}
		}	
		free_all(str_env);
		free_all(full_cmd);
		free_env(*(to_free.env));
		free_word_lst(to_free.lst);
		free_word_lst(to_free.command);
		free_tubes(to_free.tubes);
		if (g_status == 127)
			exit(127);
		else
			exit(EXIT_SUCCESS);
	}
}

void	debug_print_words(t_word **lst)
{
	t_word	*temp;

	temp = *lst;
	while (temp)
	{
		printf("word: %s\n", temp->word);
		printf("type: %d\n", temp->type);
		temp = temp->next;
	}
}

void	execute_line(t_word	**word, t_env_var **env, t_env_var **global, char *line)
{
	t_env_var	*path;
	int			pipes_nbr;
	t_word		**cmd;
	int			**tubes;
	int			count;
	t_to_free	to_free;

	count = 0;
	pipes_nbr = count_pipes(word);
	to_free.lst = word;
	to_free.env = env;
	to_free.global = global;
	to_free.line = line;
	to_free.tubes = create_tubes(pipes_nbr);
	
	to_free.command = malloc(sizeof(t_word *));
	if (!to_free.command)
		return ;
	*(to_free.command) = 0;

	while (get_next_cmd(word, &(to_free.command)))
	{
		// debug_print_words(to_free.command);
		path = get_env_custom("PATH", *env);
		if (!execute_non_fork_builtin(to_free, pipes_nbr))
			ft_execve(to_free, path, count, pipes_nbr);
		clear_word_lst(to_free.command);
		count++;
	}
	free_word_lst(to_free.command);
	free_tubes(to_free.tubes);
}
