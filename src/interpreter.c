/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:15:49 by chuhlig           #+#    #+#             */
/*   Updated: 2025/01/18 18:36:08 by chuhlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug_tools.h"
#include "minishell.h"

int	eval_rec(t_node *node, t_env **env, int in_fd);

int	open_file(char *path, int flags, int mode)
{
	int	fd;

	fd = open(path, flags, mode);
	if (fd < 0)
		perror("open");
	return (fd);
}

int	eval_rec(t_node *node, t_env **env, int in_fd)
{
	int		p[2];
	pid_t	pid;
	int		result;

	if (node->type == PIPE_NODE)
	{
		if (pipe(p) == -1)
			return (perror("pipe"), EXIT_FAILURE);
		pid = fork();
		if (pid == -1)
			return (perror("fork"), close(p[0]), close(p[1]), EXIT_FAILURE);
		if (pid == 0)
			handle_pipe_child(p, node, env, in_fd);
		result = handle_pipe_parent(p, node, env);
	}
	else if (node->type == CMD_NODE)
		result = execute_cmd(&node->content.cmd, env);
	else
		result = EXIT_FAILURE;
	return (result);
}

int	eval(t_node *node, t_env **env)
{
	return (eval_rec(node, env, STDIN_FILENO));
}
