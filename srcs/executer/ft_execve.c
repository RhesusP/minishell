/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 08:17:53 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/12 08:42:46 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static void	parent_process(int **tubes, int pid, int count, t_redir **redir, int nb_pipes)
// {
// 	int	status;

// 	status = 0;
// 	waitpid(pid, &status, 0);
// 	if (WIFEXITED(status))
// 		g_status = WEXITSTATUS(status);
// 	// Fermez les descripteurs de fichiers inutilisés pour les tubes du processus parent
//     for (int i = 0; i < nb_pipes; i++)
//     {
//         close(tubes[i][0]);
//         close(tubes[i][1]);
//     }
// 	free_redir(redir);
// }

// static void	link_processes(int **tubes, int count, int nb_pipes)
// {
// 	if (count < nb_pipes)
// 		dup2(tubes[count][1], STDOUT_FILENO);
// 	if (count > 0)
// 		dup2(tubes[count - 1][0], STDIN_FILENO);
// 	for (int i = 0; i < nb_pipes; i++) {
//         // if (i != count) {
//             close(tubes[i][0]); // Fermeture de l'extrémité de lecture du tube
//             close(tubes[i][1]); // Fermeture de l'extrémité d'écriture du tube
//         // }
//     }
// }

// static void	exec_cmd(t_to_free f, char **full_cmd, char **str_env, char *exec)
// {
// 	if (full_cmd[0] && !exec)
// 	{
// 		if (execve(full_cmd[0], full_cmd, str_env) == -1)
// 		{
// 			ft_putstr_fd(full_cmd[0], 2);
// 			ft_putendl_fd(": command not found", 2);
// 			g_status = 127;
// 		}
// 	}
// 	else
// 	{
// 		if (execve(exec, full_cmd, str_env) == -1)
// 		{
// 			ft_putstr_fd(full_cmd[0], 2);
// 			ft_putendl_fd(": command not found", 2);
// 			g_status = 127;
// 			free(exec);
// 		}
// 		printf("here\n");
// 	}
// 	printf("near of the end of exec_cmd\n");
// 	free_all(str_env);
// 	if (g_status == 127)
// 		free_and_exit(f, 1, 127);
// 	else
// 		free_and_exit(f, 1, EXIT_SUCCESS);
// }

// static void	child_process(t_to_free f, int count, int n_pp, t_redir **redir)
// {
// 	char	**full_cmd;
// 	char	**temp;
// 	char	**str_env;
// 	char	*exec_path;

// 	link_processes(f.tubes, count, n_pp);
// 	full_cmd = lst_to_string(f.command);
// 	if (redir)
// 	{
// 		temp = handle_redirection(redir, full_cmd);
// 		full_cmd = copy_string_array(temp);
// 		free_all(temp);
// 	}
// 	free_redir(redir);
// 	if (!full_cmd[0])
// 		free_and_exit(f, 1, 0);
// 	if (execute_builtin(f.command, f.env, n_pp))
// 	{
// 		free_all(full_cmd);
// 		free_and_exit(f, 1, g_status);
// 	}
// 	exec_path = get_execve_path(full_cmd[0], get_env_custom("PATH", *f.env));
// 	str_env = env_to_tab(*(f.env));
// 	exec_cmd(f, full_cmd, str_env, exec_path);
// 	printf("here in child process\n");
// }

// void	ft_execve(t_to_free to_free, int count, int nb_pipes)
// {
// 	char	**full_cmd;
// 	int		pid;
// 	t_redir	**redir;

// 	pid = fork();
// 	redir = get_redir(to_free.command);
// 	if (pid == -1)
// 		perror("failed to fork\n");
// 	if (pid > 0)
// 		parent_process(to_free.tubes, pid, count, redir, nb_pipes);
// 	if (pid == 0)
// 		child_process(to_free, count, nb_pipes, redir);
// }
