/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:23:51 by dkaiser           #+#    #+#             */
/*   Updated: 2025/01/21 13:17:47 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/fcntl.h>
#include <unistd.h>

static int	cant_write(char *filename);
static void	create_file(char *filename, int mode);

int	create_files(t_list *files)
{
	t_redirection	*file;

	while (files)
	{
		if (files->content != NULL)
		{
			file = (t_redirection *)files->content;
			if (file->type == INPUT_FILE && (access(file->specifier, F_OK) == -1
					|| access(file->specifier, R_OK) == -1))
				return (EXIT_FAILURE);
			if (cant_write(file->specifier))
				break ;
			if (file->type == OUTPUT_OVERRIDE)
				create_file(file->specifier, O_TRUNC);
			else if (file->type == OUTPUT_APPEND)
				create_file(file->specifier, O_APPEND);
			if (files->next == NULL)
				break ;
			if (((t_redirection *)files->next->content)->type == 0)
				break ;
		}
		files = files->next;
	}
	return (EXIT_SUCCESS);
}

static int	cant_write(char *filename)
{
	return (access(filename, F_OK) != -1 && access(filename, W_OK) == -1);
}

static void	create_file(char *filename, int mode)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | mode, 0644);
	if (fd != -1)
		close(fd);
}

void	q4fc(t_list **queue, t_redirection *redir)
{
	ft_lstadd_back(queue, ft_lstnew(redir));
}
