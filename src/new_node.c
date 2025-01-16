/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:21:03 by dkaiser           #+#    #+#             */
/*   Updated: 2025/01/16 18:25:54 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_node	*new_node(int type)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (node == NULL)
		return (NULL);
	node->type = type;
	return (node);
}

t_node	*new_pipe_node(t_node *left, t_node *right)
{
	t_node	*node;

	if (left == NULL || right == NULL)
		return (NULL);
	node = new_node(PIPE_NODE);
	if (node == NULL)
		return (NULL);
	node->content.pipe.left = left;
	node->content.pipe.right = right;
	return (node);
}

t_node	*new_cmd_node(char **args, t_redirection redirs[2], t_list *create_files)
{
	t_node	*node;

	node = new_node(CMD_NODE);
	if (node == NULL)
		return (NULL);
	node->content.cmd.args = args;
	if (redirs != NULL)
	{
		node->content.cmd.redirs[0] = redirs[0];
		node->content.cmd.redirs[1] = redirs[1];
		node->content.cmd.create_files = create_files;
		free(redirs);
		return (node);
	}
	return (NULL);
}

t_node	*new_string_node(char *string)
{
	t_node	*node;

	node = new_node(STRING_NODE);
	if (node == NULL)
		return (NULL);
	node->content.string = string;
	return (node);
}
