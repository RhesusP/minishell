/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:52:44 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/04/13 13:33:52 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/exec.h"

/**
 * @brief check if the CMD is a builtin
 * UNTESTED YET
*/
int	execute_builtin(t_word **lst, t_env_var *env)
{
	t_word	*curr;

	curr = *lst;
	if (ft_strcmp(curr->word , "exit") == SUCCESS)
	{
		//TODO call exit
		return (SUCCESS);
	}
	else if (ft_strcmp(curr->word, "export") == SUCCESS)
	{
		ft_export(lst, env);
		return (SUCCESS);
	}
		
	else if (ft_strcmp(curr->word, "pwd") == SUCCESS)
		return (SUCCESS);
	else if (ft_strcmp(curr->word, "unset") == SUCCESS)
		return (SUCCESS);
	else if (ft_strcmp(curr->word, "echo") == SUCCESS)		// ok
	{
		ft_echo(lst);
		return (SUCCESS);
	}
	else if (ft_strcmp(curr->word, "env") == SUCCESS)		// ok
	{
		ft_env(lst, env);
		return (SUCCESS);
	}
	else if (ft_strcmp(curr->word, "cd") == SUCCESS)
	{
		ft_cd(lst, env);
		return (SUCCESS);
	}
	return (FAILURE);
}

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
	while (i < len)
	{
		tab[i] = ft_strdup(current->word);
		current = current->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

char	*get_execve_path(char *cmd, t_env_var *path_var)
{
	int		i;
	char	*temp;
	char	*potential_path;

	i = 0;
	while (path_var->values[i])
	{
		temp = ft_strjoin(path_var->values[i], "/");
		potential_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(potential_path, X_OK) == 0)
			return (potential_path);
		free(potential_path);
		i++;
	}
	return (NULL);

}

t_redir	*create_redir(t_type type, char *path)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (0);
	redir->type = type;
	redir->filepath = path;
	redir->next = 0;
	return (redir);
}

t_redir	*get_last_redir(t_redir *lst)
{
	t_redir	*current;

	if (!lst)
		return (0);
	current = lst;
	while (current->next)
		current = current->next;
	return (current);
}

void	add_back_redir(t_redir **lst, t_redir *new)
{
	t_redir	*last;

	if (*lst == 0)
	{
		*lst = new;
		return ;
	}
	last = get_last_redir(*lst);
	last->next = new;
}

void	display_redirs(t_redir **lst)
{
	t_redir	*current;

	if (!*lst)
	{
		printf("######   REDIR LIST   ######\n");
		printf("Aucun commande.\n");
		return ;
	}
	current = *lst;
	printf("######   REDIR LIST   ######\n");
	while (current)
	{
		printf("%s\t%s\n", print_type(current->type), current->filepath);
		current = current->next;
	}
}

t_redir	**get_redir(t_word **lst)
{
	t_word	*current;
	t_redir	**redir;

	if (!*lst)
		return (0);
	current = *lst;
	redir = malloc(sizeof(t_redir *));
	if (!redir)
		return (0);
	*redir = 0;
	while (current->next)
	{
		if (current->next->type == RO || current->next->type == RI || current->next->type == ARO || current->next->type == HE)
		{
			if (current->next->next && (current->next->next->type == FILEPATH || current->next->next->type == DELIMITER))
				add_back_redir(redir, create_redir(current->next->type, current->next->next->word));
			else
			{
				perror("syntax error ?\n");
				return (0);
			}
		}
		current = current->next;
	}
	return (redir);
}

char	*get_filepath(t_word **lst)
{
	t_word	*current;
	
	current = *lst;
	while (current->next && current->next->type != FILEPATH)
		current = current->next;
	return (current->next->word);
}

char	*here_doc(char *delim)
{
	char	*line;
	char	*concat;
	t_word	*arg;
	int		i;

	concat = "";
	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
			break ;
		if (ft_strcmp(line, delim) == 0)
			break ;
		// printf("concatening %s and %s\n", concat, line);
		concat = ft_strjoin(concat, line);
		concat = ft_strjoin(concat, "\n");
	}
	return (concat);
}

char	**copy_and_add_cmd(char **full_cmd, char *new_arg)
{
	int	i;
	int	size;
	char	**new_cmd;

	size = 0;
	while (full_cmd[size])
		size++;
	new_cmd = malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (i < size)
	{
		new_cmd[i] = full_cmd[i];
		i++;
	}
	new_cmd[i] = ft_strdup(new_arg);
	free(full_cmd);
	return (new_cmd);
}

char	**handle_redirection(t_redir **lst, char **full_cmd)
{
	t_redir	*current;
	int		fd;
	char	*new_arg;
	char	**new_full_cmd;
	t_redir	*temp;

	new_full_cmd = full_cmd;
	current = *lst;
	while (current)
	{
		if (current->type == RI)
		{
			fd = open(current->filepath, O_RDONLY);
			if (fd == -1)
			{
				perror("unable to open file");
				return (0);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (current->type == RO)
		{
			fd = open(current->filepath, O_CREAT | O_WRONLY, 0644);
			if (fd == -1)
			{
				perror("unable to open file");
				return (0);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (current->type == ARO)
		{
			fd = open(current->filepath, O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (fd == -1)
			{
				perror("unable to open file");
				return (0);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (current->type == HE)
		{
			new_arg = here_doc(current->filepath);
			fd = open(".tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
			{
				perror("unable to open file");
				return (0);
			}
			ft_putstr_fd(new_arg, fd);
			dup2(fd, STDIN_FILENO);
			close(fd);
			temp = current->next;
			current->next = create_redir(RI, ".tmp");
			current->next->next = temp;			
			//new_full_cmd = copy_and_add_cmd(new_full_cmd, new_arg);
		}
		current = current->next;
	}
	return (new_full_cmd);
}

void	ft_execve(t_word **lst, t_env_var *path, int **tubes, int count, int nb_pipes, t_env_var *env)
{
	char		*exec_path;
	char		**full_cmd;
	int			pid;
	t_redir		**redir;

	pid = fork();
	redir = get_redir(lst);
	if (pid == -1)
	{
		perror("failed to fork\n");
	}
	if (pid > 0)		//parent process
	{
		if (count > 0)
		{
			close(tubes[count - 1][0]);
			close(tubes[count - 1][1]);
		}
		wait(NULL);
	}
	if (pid == 0)		//child process
	{
		if (count > 0)
		{
			dup2(tubes[count - 1][0], STDIN_FILENO);	//duplique la sortie du précedent sur l'entree de l'actuel
			close(tubes[count - 1][0]);					//ferme l'entrée / sortie du précédent
			close(tubes[count - 1][1]);
		}
		if (count < nb_pipes)
		{
			dup2(tubes[count][1], STDOUT_FILENO);	//duplique pour le suivant
			close(tubes[count][0]);
			close(tubes[count][1]);
		}
		full_cmd = lst_to_string(lst);

		if (redir)
			full_cmd = handle_redirection(redir, full_cmd);
		exec_path = get_execve_path(full_cmd[0], path);
		
		// if (execute_builtin(lst, env) != SUCCESS)
		// {
			if (!exec_path)
				execve(full_cmd[0], full_cmd, NULL);
			execve(exec_path, full_cmd, NULL);
		// }
		exit(EXIT_SUCCESS);		//TODO maybe fix the multiple exit case
	}
}

int	**create_tubes(int nb_tubes)
{
	int	i;
	int	**tubes;

	tubes = malloc(sizeof(int *) * nb_tubes);	//TODO secure
	i = 0;
	while (i < nb_tubes)
	{
		tubes[i] = malloc(sizeof(int) * 2);
		if (pipe(tubes[i]) == -1)
			perror("pipe failed.\n");		//TODO secure
		i++;
	}
	return (tubes);
}

void	execute_line(t_word	**word, t_env_var *env)
{
	t_env_var	*path;
	int			pipes_nbr;
	t_word		**cmd;
	int			**tubes;
	int			count;

	count = 0;
	pipes_nbr = count_pipes(word);
	tubes = create_tubes(pipes_nbr);	//create fd array and pipes
	cmd = malloc(sizeof(t_word *));
	if (!cmd)		//TODO catch error
		return ;
	*cmd = 0;
	while (get_next_cmd(word, &cmd))		//we execute each command
	{
		//printf("CMD LIST\n");
		//display_words(cmd);
		path = get_env_custom("PATH", env);
		//get_redir(cmd);
		if (execute_builtin(cmd, env) != SUCCESS)
			ft_execve(cmd, path, tubes, count, pipes_nbr, env);
		clear_word_lst(cmd);
		count++;
	}
}
