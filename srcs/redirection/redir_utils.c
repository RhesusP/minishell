/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 10:31:55 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/22 16:54:42 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

/**
 * @brief Search for redirections in the command and add them in the redir list.
 * 
 * @param current Word to check.
 * @param redir Redir chained list to store redirections.
 * @return 1 if no error, 0 if error.
 */
static int	search_redir(t_word *current, t_redir **redir)
{
	while (current)
	{
		if (type_is_redir(current))
		{
			if (current->next && (current->next->type == FILEPATH || \
				current->next->type == DELIMITER))
			{
				add_back_redir(redir, create_redir(current->type, \
					current->next->word));
			}
			else
			{
				perror("syntax error\n");
				return (0);
			}
		}
		current = current->next;
	}
	return (1);
}

/**
 * @brief Allocates memory for the redir list and calls search_redir()
 * to fill it.
 * 
 * @param lst Word chained list to check for redirections.
 * @return t_redir** 
 */
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
	if (!search_redir(current, redir))
		return (0);
	return (redir);
}

/**
 * @brief Display the here document prompt and concatenate
 * the lines until it find a delimiter.
 * 
 * @param delim Here document delimiter.
 * @return char* Concatenated lines.
 */
char	*here_doc(char *delim)
{
	char	*line;
	char	*concat;

	g_gbl.in_hd = 1;
	concat = "";
	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
			break ;
		if (ft_strcmp(line, delim) == 0)
			break ;
		concat = ft_strjoin(concat, line);
		concat = ft_strjoin(concat, "\n");
	}
	return (concat);
}

/**
 * @brief Handle simple redirections (`>` and `<`)
 * 
 * @param current Current redirection.
 * @return 1 if no error, 0 if error.
 */
int	handle_simple_redir(t_redir *current)
{
	if (current->type == RI)
	{
		if (!input_redirection(current))
			return (0);
	}
	if (current->type == RO)
	{
		if (!output_redirection(current))
			return (0);
	}
	return (1);
}

/**
 * @brief Handle redirections in the command.
 * @details Search for redirections in the command, handle by redirecting
 * tubes and free the redir list.
 * @param to_free
 * @param full_cmd Pointer to the command to execute. 
 * @param i Index of the current sub-command.
 */
void	do_exec_redir(t_to_free *to_free, char ***full_cmd, int i)
{
	char	**temp;

	g_gbl.redir = get_redir(to_free->command);
	if (g_gbl.redir)
	{
		temp = handle_redirection(g_gbl.redir, *full_cmd, to_free->he_files[i]);
		if (!temp)
		{
			free_redir(g_gbl.redir);
			g_gbl.redir = 0;
			free_all(*full_cmd);
			free_and_exit(to_free, 1, g_gbl.status, 1);
		}
		*full_cmd = copy_string_array(temp);
		free_all(temp);
	}
	free_redir(g_gbl.redir);
	g_gbl.redir = 0;
}
