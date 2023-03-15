/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:52:44 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/03/08 14:04:40 by tbarde-c         ###   ########.fr       */
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

char	**get_full_cmd(t_word *word)
{
	char	**cmd;
	int		i;
	int		arg_len;

	arg_len = get_arg_len(word);
	i = 0;
	cmd = malloc(sizeof(char *) * (arg_len + 1));
	while(i < arg_len)
	{
		cmd[i] = word->word;
		i++;
	}
	cmd[i] = NULL;
	return (cmd);
}

char	*get_execve_path(t_word *word, t_env_var *path)
{
	char		*execve_path;
	int			i;

	i = 0;
	execve_path = NULL;
	while (path->values[i])
	{
		execve_path = ft_strjoin_custom(path->values[i], word->word);
		if (access(execve_path, X_OK) == 0)
			return (execve_path);
		free(execve_path);
		i++;
	}
	return (NULL);

}
int	is_execve(t_word *word, t_env_var *path)
{
	char		*execve_path;
	char		**full_cmd;
	int			pid;

	pid = fork();
	if (pid == -1)
		return 1;
	if (pid > 0)
		wait(NULL);
	if (pid == 0)
	{
		full_cmd = get_full_cmd(word);
		execve_path = get_execve_path(word, path);
		execve(execve_path, full_cmd, NULL);
		free_all(full_cmd);
	}
	return 0;
}

void	execute_line(t_word	*word, t_env_var *env)
{
	t_env_var	*path;

	
	path = get_env_custom("PATH", env);
	if (word->type == CMD)
	{
		//if (is_builtin(word->word) == FAILURE)
			is_execve(word, path);
		//then advance till the next command ?
	}

}
