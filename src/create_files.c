/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:23:51 by dkaiser           #+#    #+#             */
/*   Updated: 2025/01/20 15:54:00 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

int	create_files(t_list *files)
{
	t_redirection	*file;
	int				fd;

	while (files)
	{
        if (files->content == NULL)
        {
            files = files->next;
            continue ;
        }
		file = (t_redirection *)files->content;
        if (file->type == INPUT_FILE && (access(file->specifier, F_OK) == -1 || access(file->specifier, R_OK) == -1))
            return (EXIT_FAILURE);
        if (access(file->specifier, F_OK) != -1 && access(file->specifier, W_OK) == -1)
            break ;
		if (file->type == OUTPUT_OVERRIDE)
		{
			fd = open(file->specifier, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			close(fd);
		}
		else if (file->type == OUTPUT_APPEND)
		{
			fd = open(file->specifier, O_WRONLY | O_CREAT | O_APPEND, 0644);
			close(fd);
		}
        if (files->next == NULL)
             break ;
        if (((t_redirection *) files->next->content)->type == 0)
             break ;
		files = files->next;
	}
    return (EXIT_SUCCESS);
}
