/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrows.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 11:14:29 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/03/08 14:02:08 by tbarde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/exec.h"

/**
*  @brief ">" (Write in file)
**/
int     single_right_arrow(char *file_path, char *to_write)
{
        int     fd;

        fd = open(file_path, O_WRONLY, O_CREAT);
        if (fd == -1)
                return (FAILURE);
        write(fd, to_write, ft_strlen(to_write));
        return (SUCCESS);
}

/**
*	@brief ">>" (Write in file APPEND)
**/
int     double_right_arrow(char *file_path, char *to_write)
{
        int     fd;

        fd = open(file_path, O_WRONLY, O_APPEND, O_CREAT);
        if (fd == -1)
                return (FAILURE);
        write(fd, to_write, ft_strlen(to_write));
        return (SUCCESS);
}
