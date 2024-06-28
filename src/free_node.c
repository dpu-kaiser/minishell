/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:41:46 by dkaiser           #+#    #+#             */
/*   Updated: 2024/06/28 14:51:10 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static void	free_assign_node(t_node *node);
static void	free_pipe_node(t_node *node);
static void	free_cmd_node(t_node *node);

void	free_node(t_node *node)
{
	if (node->type == ASSIGN)
		free_assign_node(node);
	else if (node->type == PIPE)
		free_pipe_node(node);
	else if (node->type == CMD)
		free_cmd_node(node);
	else if (node->type == STRING)
		free(node->content.string);
	else
		panic(UNREACHABLE);
	free(node);
}

static void	free_assign_node(t_node *node)
{
	free(node->content.assign.var);
	free(node->content.assign.value);
}

static void	free_pipe_node(t_node *node)
{
	free_node(node->content.pipe.left);
	free_node(node->content.pipe.right);
}

static void	free_cmd_node(t_node *node)
{
	int	i;

	i = 0;
	while (node->content.cmd.args[i] != NULL)
	{
		free(node->content.cmd.args[i]);
		i++;
	}
	free(node->contents.cmd.args);
	free(node->content.cmd.redirs[0].specifier);
	free(node->content.cmd.redirs[1].specifier);
}
