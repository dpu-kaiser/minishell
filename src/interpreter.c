/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 13:15:24 by dkaiser           #+#    #+#             */
/*   Updated: 2024/08/05 13:33:16 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	eval_pipe(t_pipe *pipe);
static int	eval_cmd(t_cmd *cmd);

int	eval(t_node *node)
{
	if (node->type == PIPE_NODE)
		return (eval_pipe(&node->content.pipe));
	else if (node->type == CMD_NODE)
		return (eval_cmd(&node->content.cmd));
	else
	{
		panic(UNREACHABLE);
		return (-1);
	}
}

static int	eval_pipe(t_pipe *pipe)
{
	return (0);
}

static int	eval_cmd(t_cmd *cmd)
{
	return (0);
}
