/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 00:33:42 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/22 16:56:48 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Handle the case where execve() fails.
 * @details It prints the error message, set the appropriate exit status, free
 * allocated variables and exit program.
 * @param f 
 * @param cmd Current command passed in execve().
 * @param env Environment in a string array.
 * @param nb_p Number of pipes in the current command.
 */
void	handle_execve_fail(t_to_free *f, char **cmd, char **env, int nb_p)
{
	ft_putstr_fd(cmd[0], STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	g_gbl.status = 127;
	unlink_he_files(f, nb_p);
	free_all(cmd);
	free_all(env);
	g_gbl.str_env = 0;
	free_and_exit(f, 1, g_gbl.status, 0);
}

/**
 * @brief Print appropriate error message, set the appropriate exit status,
 * free allocated memory and exit program.
 * 
 * @param f 
 * @param cmd Current command passed in execve().
 * @param msg Error message to display.
 * @param status Exit status to set.
 */
static void	exit_with_error(t_to_free *f, char **cmd, char *msg, int status)
{
	ft_putstr_fd(cmd[0], STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	g_gbl.status = status;
	free_all(cmd);
	free_and_exit(f, 1, g_gbl.status, 0);
}

/**
 * @brief Check if the path is a directory and if it is executable.
 * 
 * @param f 
 * @param cmd Current command passed in execve().
 * @param nb_pipes Number of pipes in the current command.
 * @param path path to check.
 */
void	check_dir_err(t_to_free *f, char **cmd, int nb_pipes, struct stat path)
{
	if (S_ISDIR(path.st_mode))
	{
		unlink_he_files(f, nb_pipes);
		exit_with_error(f, cmd, ": Is a directory\n", 126);
	}
	else
	{
		if (access(cmd[0], X_OK) != 0)
		{
			unlink_he_files(f, nb_pipes);
			exit_with_error(f, cmd, ": Permission denied\n", 126);
		}
	}
}

/**
 * @brief Check if a command is valid and executable. If not, set the appropriate
 * exit status, free and exit the program.
 * @details It checks if a command is valid by checking if the path exists,
 * if it is a directory and if it is executable.
 * 
 * @param f 
 * @param cmd Current command passed in execve().
 * @param nb_pipes Number of pipes in the current command.
 */
void	check_cmd_err(t_to_free *f, char **cmd, int nb_pipes)
{
	struct stat	path;

	if (stat(cmd[0], &path) == 0)
		check_dir_err(f, cmd, nb_pipes, path);
	else
	{
		if (ft_strncmp(cmd[0], "./", 2) == 0)
		{
			unlink_he_files(f, nb_pipes);
			exit_with_error(f, cmd, ": No such file or directory\n", 127);
		}
	}
}
