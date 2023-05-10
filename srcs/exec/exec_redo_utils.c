#include "../../includes/minishell.h"
// #include "../../includes/exec.h"

/**
 * @brief strjoin but adds a '/' between the two char* joined
 * @return joined char *
**/
char	*ft_strjoin_custom(char const *s1, char const *s2)
{
	char	*res;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (0);
	res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!res)
		return (res);
	i = 0;
	while (s1[i] != '\0')
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = '/';
	i++;
	j = 0;
	while (s2[j] != '\0')
	{
		res[i] = s2[j];
		i++;
		j++;
	}
	res[i] = '\0';
	return (res);
}

/**
*	@brief Get the number of args for the execution of one programm
**/
int	get_exec_len(t_word **lst)
{
	int		len;
	t_word	*current;

	len = 0;
	current = *lst;
	while (current && (current->type == CMD || current->type == ARG))
	{
		len++;
		current = current->next;
	}
	return (len);
}

// /**
// *	@brief Free char **
// **/
// void	free_all(char **str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		free(str[i]);
// 		i++;
// 	}
// 	free(str);
// }

/**
 * @brief Counts the number of pipe that were parsed
 * @return Number of pipes counted
**/
int	count_pipes(t_word **word)
{
	int		pipe_nbr;
	t_word	*current;

	pipe_nbr = 0;
	if (!*word)
		return (0);
	current = *word;
	while (current)
	{
		if (current->type == PIPE)
			pipe_nbr++;
		current = current->next;
	}
	return (pipe_nbr);
}
