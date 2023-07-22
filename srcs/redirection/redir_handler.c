/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 21:18:54 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/22 13:54:12 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

/**
 * @brief Duplicate tubes to do an input redirection.
 * 
 * @param current 
 * @return 1 if no error, 0 if error.
 */
int	input_redirection(t_redir *current)
{
	int	fd;

	fd = open(current->filepath, O_RDONLY);
	if (fd == -1)
	{
		perror(current->filepath);
		g_gbl.status = 1;
		return (0);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (1);
}

/**
 * @brief Duplicate tubes to do an output redirection.
 * 
 * @param current 
 * @return 1 if no error, 0 if error.
 */
int	output_redirection(t_redir *current)
{
	int	fd;

	fd = open(current->filepath, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(current->filepath);
		g_gbl.status = 1;
		return (0);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}

/**
 * @brief Duplicate tubes to do an output append redirection.
 * 
 * @param current 
 * @return 1 if no error, 0 if error.
 */
static int	output_app_redirection(t_redir *current)
{
	int	fd;

	fd = open(current->filepath, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(current->filepath);
		g_gbl.status = 1;
		return (0);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}

/**
 * @brief Duplicate tubes to do a here document redirection.
 *
 * @param current
 * @param he_file The file to write the here document.
 * @return 1 if no error, 0 if error.
 */
static int	here_doc_redirection(t_redir *current, char *he_file)
{
	int		fd;
	char	*new_arg;
	t_redir	*temp;

	new_arg = here_doc(current->filepath);
	fd = open(he_file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(current->filepath);
		g_gbl.status = 1;
		return (0);
	}
	ft_putstr_fd(new_arg, fd);
	dup2(fd, STDIN_FILENO);
	close(fd);
	temp = current->next;
	current->next = create_redir(RI, he_file);
	current->next->next = temp;
	return (1);
}

/**
 * @brief Handle redirections.
 * 
 * @param lst List of redirections.
 * @param full_cmd Command to execute.
 * @param he_file The file to write the here document.
 * @return char** the new command to execute.
 */
char	**handle_redirection(t_redir **lst, char **full_cmd, char *he_file)
{
	t_redir	*current;
	char	**new_full_cmd;

	new_full_cmd = full_cmd;
	current = *lst;
	while (current)
	{
		if (!handle_simple_redir(current))
			return (0);
		else if (current->type == ARO)
		{
			if (!output_app_redirection(current))
				return (0);
		}
		else if (current->type == HE)
		{
			if (!here_doc_redirection(current, he_file))
				return (0);
		}
		current = current->next;
	}
	return (new_full_cmd);
}
