/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 13:15:24 by dkaiser           #+#    #+#             */
/*   Updated: 2024/10/25 20:59:16 by chuhlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug_tools.h"
#include "minishell.h"
#include <stdlib.h>
#include <sys/_types/_pid_t.h>
#include <sys/cdefs.h>
#include <sys/wait.h>
#include <unistd.h>

static int	eval_rec(t_node *node, t_env *env, int in_fd);

int	eval(t_node *node, t_env *env)
{
	pid_t	pid;
	int		result;

	if (node == NULL)
		return (EXIT_FAILURE);
	result = 0;
	pid = fork();
	if (pid < 0)
	{
		return (EXIT_FAILURE);
	}
	if (pid == 0)
	{
		result = eval_rec(node, env, STDIN_FILENO);
		exit(result);
	}
	else
	{
		waitpid(pid, &result, 0);
	}
	return (result);
}

static int	eval_rec(t_node *node, t_env *env, int in_fd)
{
	pid_t	pid;
	int		result;
	int		p[2];

	result = pipe(p);
	if (result == -1)
		return (EXIT_FAILURE);
	if (node->type == PIPE_NODE)
	{
		pid = fork();
		if (pid < 0)
		{
			return (EXIT_FAILURE);
		}
		if (pid == 0)
		{
			close(p[0]);
			dup2(in_fd, STDIN_FILENO);
			dup2(p[1], STDOUT_FILENO);
			result = execute_cmd(&node->content.pipe.left->content.cmd, env);
			exit(result);
		}
		else
		{
			close(p[1]);
			dup2(p[0], STDIN_FILENO);
			result = eval_rec(node->content.pipe.right, env, p[0]);
		}
	}
	else if (node->type == CMD_NODE)
	{
		result = execute_cmd(&node->content.cmd, env);
	}
	else
	{
		panic(UNREACHABLE);
		return (EXIT_FAILURE);
	}
	return (result);
}

