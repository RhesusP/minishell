/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:52:44 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/03/26 16:06:30 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/exec.h"

/**
 * @brief check if the CMD is a builtin
 * UNTESTED YET
*/
/*static int	is_builtin(t_word *word)
{
	if (ft_strcmp(word->word, "exit") == SUCCESS)
		//return(exec_exit(), SUCCESS)
	if (ft_strcmp(word->word, "export") == SUCCESS)
		//return(exec_export(), SUCCESS)
	if (ft_strcmp(word->word, "pwd") == SUCCESS)
		//return(exec_pwd(), SUCCESS)
	if (ft_strcmp(word->word, "unset") == SUCCESS)
		//return(exec_unset(), SUCCESS)
	if (ft_strcmp(word->word, "echo") == SUCCESS)
		//return(exec_echo(), SUCCESS)
	if (ft_strcmp(word->word, "env") == SUCCESS)
		//return(exec_env(), SUCCESS)
	return (FAILURE);

}*/



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
int	ft_execve(t_word **lst, t_env_var *path)		//TODO why returning int ?
{
	char		*exec_path;
	char		**full_cmd;
	int			pid;

	pid = fork();
	if (pid == -1)
		return 1;
	if (pid > 0)
		wait(NULL);
	if (pid == 0)
	{
		full_cmd = lst_to_string(lst);
		exec_path = get_execve_path(full_cmd[0], path);
		if (!exec_path)
			execve(full_cmd[0], full_cmd, NULL);
		execve(exec_path, full_cmd, NULL);
	}
	return (0);
}

void	execute_line(t_word	**word, t_env_var *env)
{
	t_env_var	*path;
	int			pipes_nbr;
	t_word		**cmd;

	pipes_nbr = count_pipes(word);
	printf("%d pipes\n", pipes_nbr);
	cmd = malloc(sizeof(t_word *));
	if (!cmd)		//TODO catch error
		return ;
	*cmd = 0;
	while (get_next_cmd(word, &cmd))
	{
		path = get_env_custom("PATH", env);
		ft_execve(cmd, path);		

		// printf("\033[95m------ CMD ------\n");
		// display_words(cmd);
		// printf("\033[39m\n");
		clear_word_lst(cmd);
	}

	/*
	path = get_env_custom("PATH", env);
	if (word->type == CMD)
	{
		//if (is_builtin(word->word) == FAILURE)
			is_execve(word, path);
		//then advance till the next command ?
	}
	*/
}
