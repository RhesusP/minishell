/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 19:27:54 by cbernot           #+#    #+#             */
/*   Updated: 2023/05/12 14:32:42 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	g_status = 0;

int	type_is_redir(t_word *word)
{
	if(word->type == RI || word->type == RO || word->type == ARO || word->type == HE)
		return (1);
	return (0);
}

int	is_bad_filepath(t_word *word)
{
	if (word->type == FILEPATH)
	{
		if (ft_strcmp(">", word->word) == 0 || ft_strcmp("<", word->word) == 0 || ft_strcmp(">>", word->word) == 0 || ft_strcmp("<<", word->word) == 0)
			return (1);
	}
	return (0);
}

int	print_syntax_error(char *token)
{
	g_status = 2;
	ft_putstr_fd("syntax error near unexpected token '", 2);
	ft_putstr_fd(token, 2);
	ft_putendl_fd("'", 2);
 	return (1);
}

int	syntax_error(t_word **lst)
{
	t_word	*current;

	if (!lst || !*lst)
		return (0);
	current = *lst;
	while (current)
	{
		if (type_is_redir(current) && !current->next)
			return (print_syntax_error("newline"));
		if (current->next)
		{
			if (type_is_redir(current) && (type_is_redir(current->next) || is_bad_filepath(current->next)))
				return (print_syntax_error(current->next->word));
		}
		current = current->next;
	}
	return (0);
}

int	get_env_size(t_env_var *env)
{
	t_env_var	*current;
	int			size;

	size = 0;
	if (!env)
		return (0);
	current = env;
	while (current)
	{
		size++;
		current = current->next;
	}
	return (size);
}

char	*join_env_values(char *key, char **tab)
{
	char	*res;
	int		i;

	res = ft_strdup(key);
	res = ft_strjoin(res, "=");
	i = 0;
	while (tab[i])
	{
		res = ft_strjoin(res, tab[i]);
		if (tab[i + 1])
			res = ft_strjoin(res, ":");
		i++;
	}
	return (res);
}

char	**env_to_tab(t_env_var *env)
{
	t_env_var	*current;
	char		**tab;
	int			cell;

	if (!env)
		return (0);
	
	tab = malloc(sizeof(char *) * (get_env_size(env) + 1));
	if (!tab)
		return (0);
	current = env;
	cell = 0;
	while (current)
	{
		tab[cell] = join_env_values(current->key, current->values);
		cell++;
		current = current->next;
	}
	tab[cell] = 0;
	return (tab);
}

void	free_words_lst(t_word **lst)
{
	t_word	*current;
	t_word	*next;

	if (!lst)
		return ;
	current = *lst;
	while (current)
	{
		next = current->next;
		free(current->word);
		free(current);
		current = next;
	}
	free(lst);
}

int	main(int argc, char **argv, char **envp)
{
	t_env_var	*env_vars;
	t_env_var	*global_vars;
	char		*line;
	t_word		**words_lst;

	(void)argv;
	if (argc != 1)
	{
		ft_putstr_fd("[!] USAGE: ./minishell\n", 2);
		return (0);
	}
	signal_handler();
	env_vars = get_environment(envp);
	global_vars = malloc(sizeof(t_env_var));
	global_vars = 0;
	while (1)
	{
		line = readline("\033[1;36mminishell $>\033[00m ");
		handle_ctrld(line);
		if (!is_cmd_anonymous(line))
			add_history(line);
		words_lst = parse_words(line, &global_vars);
		printf("\033[95m\texpansion start\033[39m\n");
		var_expansion(words_lst, &global_vars, &env_vars);
		printf("\033[95m\texpansion finished\033[39m\n");
		if (words_lst && *words_lst && !syntax_error(words_lst))
			execute_line(words_lst, &env_vars, &global_vars);
		free(line);
	}
	//ft_free(env_vars, global_vars);
	return (0);
}
