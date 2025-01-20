/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:23:51 by dkaiser           #+#    #+#             */
/*   Updated: 2025/01/19 14:36:59 by chuhlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

void	create_files(t_list *files)
{
	t_redirection	*file;
	int				fd;

	while (files)
	{
        dbg("Test");
        if (files->content == NULL)
            continue ;
		file = (t_redirection *)files->content;
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
}
