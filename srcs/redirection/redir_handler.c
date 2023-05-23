/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 21:18:54 by cbernot           #+#    #+#             */
/*   Updated: 2023/05/21 20:04:56 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

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
	while (current)
	{
		if (current->type == RO || current->type == RI || current->type == ARO || current->type == HE)
		{
			if (current->next && (current->next->type == FILEPATH || current->next->type == DELIMITER))
				add_back_redir(redir, create_redir(current->type, current->next->word));
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
		concat = ft_strjoin(concat, line);
		concat = ft_strjoin(concat, "\n");
	}
	return (concat);
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
				perror(current->filepath);
				return (0);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (current->type == RO)
		{
			fd = open(current->filepath, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (fd == -1)
			{
				perror(current->filepath);
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
				perror(current->filepath);
				return (0);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (current->type == HE)
		{
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
		}
		current = current->next;
	}
	return (new_full_cmd);
}