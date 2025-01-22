/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:41:46 by dkaiser           #+#    #+#             */
/*   Updated: 2025/01/22 01:53:34 by chuhlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static void	free_pipe_node(t_node *node);
static void	free_cmd_node(t_node *node);
static void	free_file(void *arg);

// void	free_node(t_node *node)
// {
// 	if (node->type == PIPE_NODE)
// 		free_pipe_node(node);
// 	else if (node->type == CMD_NODE)
// 		free_cmd_node(node);
// 	else if (node->type == STRING_NODE)
// 		free(node->content.string);
// 	else
// 		panic(UNREACHABLE);
// 	free(node);
// }
void	free_redirections(t_redirection redirs[2])
{
    for (int i = 0; i < 2; i++)
    {
        if (redirs[i].specifier)
            free(redirs[i].specifier);
    }
}

void	free_node(t_node *node)
{
    if (!node)
        return;

    if (node->type == PIPE_NODE)
    {
        free_node(node->content.pipe.left);
        free_node(node->content.pipe.right);
    }
    else if (node->type == CMD_NODE)
    {
        if (node->content.cmd.args)
        {
            for (int i = 0; node->content.cmd.args[i]; i++)
                free(node->content.cmd.args[i]);
            free(node->content.cmd.args);
        }
        free_redirections(node->content.cmd.redirs);
        // Assuming create_files is a list of dynamically allocated strings
        t_list *current = node->content.cmd.create_files;
        t_list *next;
        while (current)
        {
            next = current->next;
            free(current->content);
            free(current);
            current = next;
        }
    }
    else if (node->type == STRING_NODE)
    {
        free(node->content.string);
    }
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
	if (node->content.cmd.create_files != NULL)
		ft_lstclear(&node->content.cmd.create_files, free_file);
}

static void	free_file(void *arg)
{
	t_redirection	*file;

	file = (t_redirection *)arg;
	free(file->specifier);
	free(file);
}
