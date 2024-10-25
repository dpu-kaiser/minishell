/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 13:15:24 by dkaiser           #+#    #+#             */
/*   Updated: 2024/10/25 15:46:53 by chuhlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

static int	eval_pipe(t_pipe *pipe, t_env *env);
static int	eval_cmd(t_cmd *cmd, t_env **env);

int	eval(t_node *node, t_env **env)
{
	if (node->type == PIPE_NODE)
		return (eval_pipe(&node->content.pipe, *env));
	else if (node->type == CMD_NODE)
		return (eval_cmd(&node->content.cmd, env));
	else
	{
		panic(UNREACHABLE);
		return (-1);
	}
}

static int	eval_pipe(t_pipe *pipe, t_env *env)
{
	dbg("TODO: PIPE");
	eval_cmd(&pipe->left->content.cmd, &env);
	eval_cmd(&pipe->right->content.cmd, &env);
	return (0);
}

static int	eval_cmd(t_cmd *cmd, t_env **env)
{
	if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		pwd(*env);
	else if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		echo(cmd->args);
	else if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		ft_env(*env);
	else if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		cd(env, cmd->args);
	else if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
		unset(cmd->args, env);
	else if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		export(cmd->args, env);
	return (0);
}
