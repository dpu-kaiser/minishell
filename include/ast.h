/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:48:27 by dkaiser           #+#    #+#             */
/*   Updated: 2025/01/18 18:56:04 by chuhlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H
# include "debug_tools.h"
# include "stdlib.h"

enum						e_node_type
{
	PIPE_NODE,
	CMD_NODE,
	STRING_NODE
};

typedef struct s_pipe
{
	struct s_node			*left;
	struct s_node			*right;
}							t_pipe;

enum						e_redirection_type
{
	INPUT_FILE = 1,
	INPUT_LIMITER = 2,
	OUTPUT_OVERRIDE = 4,
	OUTPUT_APPEND = 8
};

typedef struct s_redirection
{
	int						type;
	char					*specifier;
}							t_redirection;

typedef struct s_cmd
{
	char					**args;
	struct s_redirection	redirs[2];
}							t_cmd;

union						u_node_content
{
	struct s_pipe			pipe;
	struct s_cmd			cmd;
	char					*string;
};

typedef struct s_node
{
	int						type;
	union u_node_content	content;
}							t_node;

t_node						*new_node(int type);
t_node						*new_pipe_node(t_node *left, t_node *right);
t_node						*new_cmd_node(char **args, t_redirection redirs[2]);
t_node						*new_string_node(char *string);

void						free_node(t_node *node);

#endif