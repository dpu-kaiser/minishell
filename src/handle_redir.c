/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 18:34:51 by chuhlig           #+#    #+#             */
/*   Updated: 2025/01/20 15:24:49 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_input_redirection(t_redirection *redir)
{
	int	fd;

	if (redir->type == INPUT_FILE)
	{
		fd = open_file(redir->specifier, O_RDONLY, 0);
		if (fd < 0)
			return (-1);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (redir->type == INPUT_LIMITER)
	{
		fd = open_file("/tmp/heredoc_tmp", O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
			return (-1);
		write(fd, redir->specifier, ft_strlen(redir->specifier));
		close(fd);
		fd = open_file("/tmp/heredoc_tmp", O_RDONLY, 0);
		if (fd < 0)
			return (-1);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	return (0);
}

int	handle_output_redirection(t_redirection *redir)
{
	int	fd;

	if (redir->type == OUTPUT_OVERRIDE)
	{
		fd = open_file(redir->specifier, O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
			return (-1);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (redir->type == OUTPUT_APPEND)
	{
		fd = open_file(redir->specifier, O_WRONLY | O_APPEND, 0644);
		if (fd < 0)
			return (-1);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (0);
}

int	handle_redirections(t_redirection *redirs)
{
	if (redirs[0].type == INPUT_FILE || redirs[0].type == INPUT_LIMITER)
	{
		if (handle_input_redirection(&redirs[0]) < 0)
			return (-1);
	}
	if (redirs[1].type == OUTPUT_OVERRIDE || redirs[1].type == OUTPUT_APPEND)
	{
		if (handle_output_redirection(&redirs[1]) < 0)
			return (-1);
	}
	return (0);
}

int	handle_pipe_parent(int p[2], t_node *node, t_env **env)
{
	int	original_stdin;
	int	result;

	close(p[1]);
	original_stdin = dup(STDIN_FILENO);
	dup2(p[0], STDIN_FILENO);
	result = eval_rec(node->content.pipe.right, env, p[0]);
	dup2(original_stdin, STDIN_FILENO);
	close(original_stdin);
	close(p[0]);
	return (result);
}

int	handle_pipe_child(int p[2], t_node *node, t_env **env, int in_fd)
{
	close(p[0]);
	dup2(in_fd, STDIN_FILENO);
	dup2(p[1], STDOUT_FILENO);
	close(p[1]);
	exit(eval_rec(node->content.pipe.left, env, in_fd));
}
