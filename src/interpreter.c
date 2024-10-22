/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 13:15:24 by dkaiser           #+#    #+#             */
/*   Updated: 2024/10/22 15:42:07 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug_tools.h"
#include "minishell.h"
#include <stdlib.h>
#include <sys/_types/_pid_t.h>
#include <sys/cdefs.h>
#include <sys/wait.h>
#include <unistd.h>

int	eval_rec(t_node *node, t_env *env);

int	eval(t_node *node, t_env *env)
{
	pid_t	pid;
	int		result;

	result = 0;
	pid = fork();
	if (pid < 0)
	{
		return (EXIT_FAILURE);
	}
	if (pid == 0)
	{
		result = eval_rec(node, env);
		exit(result);
	}
	else
	{
		waitpid(pid, &result, 0);
	}
	return (result);
}

int	eval_rec(t_node *node, t_env *env)
{
	pid_t	pid;
	int		result;

	if (node->type == PIPE_NODE)
	{
		pid = fork();
		if (pid < 0)
		{
			return (EXIT_FAILURE);
		}
		if (pid == 0)
		{
			result = execute_cmd(&node->content.pipe.left->content.cmd, env);
			exit(result);
		}
		else
		{
			result = eval(node->content.pipe.right, env);
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
