/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:16:53 by dkaiser           #+#    #+#             */
/*   Updated: 2024/08/11 12:26:00 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_ast_rec(t_node *ast, int indent);
static void	print_cmd_node(t_node *ast, int indent);

void	print_ast(t_node *ast)
{
	if (DEBUG)
	{
		printf("\e[94m[AST]\n");
		print_ast_rec(ast, 0);
		printf("\e[0m\n");
	}
}

static void	print_ast_rec(t_node *ast, int indent)
{
	if (ast->type == CMD_NODE)
		print_cmd_node(ast, indent);
	else if (ast->type == PIPE_NODE)
	{
		printf("\n%*s%s", indent, "", "* PIPE");
		print_ast_rec(ast->content.pipe.left, indent + 2);
		print_ast_rec(ast->content.pipe.right, indent + 2);
	}
}

static void	print_cmd_node(t_node *ast, int indent)
{
	int	i;

	printf("\n%*s%s", indent, "", "* CMD");
	i = 0;
	printf("\n%*sARGS:", indent + 2, "");
	while (ast->content.cmd.args != NULL && ast->content.cmd.args[i] != NULL)
	{
		printf(" '%s'", ast->content.cmd.args[i]);
		i++;
	}
	printf("\n%*sREDIRS:", indent + 2, "");
	printf("\n%*sIN: %d %s", indent + 4, "", ast->content.cmd.redirs[0].type,
		ast->content.cmd.redirs[0].specifier);
	printf("\n%*sOUT: %d %s", indent + 4, "", ast->content.cmd.redirs[1].type,
		ast->content.cmd.redirs[1].specifier);
}
