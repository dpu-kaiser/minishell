/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 13:15:24 by dkaiser           #+#    #+#             */
/*   Updated: 2024/10/17 16:01:23 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	eval_pipe(t_pipe *pipe, t_env *env);
static int	eval_cmd(t_cmd *cmd, t_env *env);

int	eval(t_node *node, t_env *env)
{
	if (node->type == PIPE_NODE)
		return (eval_pipe(&node->content.pipe, env));
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
	eval_cmd(&pipe->left->content.cmd, env);
	eval_cmd(&pipe->right->content.cmd, env);
	return (0);
}

static int	eval_cmd(t_cmd *cmd, t_env *env)
{
	printf("%s\n", cmd->args[0]);
	printf("PATH=%s\n", env_get(env, "PATH"));
	return (0);
}
