/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 21:18:54 by cbernot           #+#    #+#             */
/*   Updated: 2023/06/16 16:20:23 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

static int	input_redirection(t_redir *current)
{
	int	fd;

	fd = open(current->filepath, O_RDONLY);
	if (fd == -1)
	{
		perror(current->filepath);
		return (0);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (1);
}

static int	output_redirection(t_redir *current)
{
	int	fd;

	fd = open(current->filepath, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(current->filepath);
		return (0);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}

static int	output_app_redirection(t_redir *current)
{
	int	fd;

	fd = open(current->filepath, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(current->filepath);
		return (0);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}

static int	here_doc_redirection(t_redir *current)
{
	int		fd;
	char	*new_arg;
	t_redir	*temp;

	new_arg = here_doc(current->filepath);
	fd = open(".tmp.c", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(current->filepath);
		return (0);
	}
	ft_putstr_fd(new_arg, fd);
	dup2(fd, STDIN_FILENO);
	close(fd);
	temp = current->next;
	current->next = create_redir(RI, ".tmp.c");
	current->next->next = temp;
	return (1);
}

char	**handle_redirection(t_redir **lst, char **full_cmd)
{
	t_redir	*current;
	char	**new_full_cmd;

	new_full_cmd = full_cmd;
	current = *lst;
	while (current)
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
		else if (current->type == ARO)
		{
			if (!output_app_redirection(current))
				return (0);
		}
		else if (current->type == HE)
		{
			if (!here_doc_redirection(current))
				return (0);
		}
		current = current->next;
	}
	return (new_full_cmd);
}