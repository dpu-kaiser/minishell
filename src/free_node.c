/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:41:46 by dkaiser           #+#    #+#             */
/*   Updated: 2024/08/11 12:26:20 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static void	free_pipe_node(t_node *node);
static void	free_cmd_node(t_node *node);

void	free_node(t_node *node)
{
	if (node->type == PIPE_NODE)
		free_pipe_node(node);
	else if (node->type == CMD_NODE)
		free_cmd_node(node);
	else if (node->type == STRING_NODE)
		free(node->content.string);
	else
		panic(UNREACHABLE);
	free(node);
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
	while (node->content.cmd.args != NULL && node->content.cmd.args[i] != NULL)
	{
		free(node->content.cmd.args[i]);
		i++;
	}
	free(node->content.cmd.args);
	if (node->content.cmd.redirs[0].type != 0
		&& node->content.cmd.redirs[0].specifier != NULL)
		free(node->content.cmd.redirs[0].specifier);
	if (node->content.cmd.redirs[1].type != 0
		&& node->content.cmd.redirs[0].specifier != NULL)
		free(node->content.cmd.redirs[1].specifier);
}
