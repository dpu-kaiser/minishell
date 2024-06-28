/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:48:27 by dkaiser           #+#    #+#             */
/*   Updated: 2024/06/28 14:56:55 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "debug_tools.h"

typedef struct s_sequence
{
	struct s_node			**nodes;
}							t_sequence;

enum						e_node_type
{
	ASSIGN_NODE,
	PIPE_NODE,
	CMD_NODE,
	STRING_NODE
};

typedef struct s_assign
{
	char					*var;
	char					*value;
}							t_assign;

typedef struct s_pipe
{
	struct s_node			*left;
	struct s_node			*right;
}							t_pipe;

enum						e_redirection_type
{
	INPUT_FILE,
	INPUT_LIMITER,
	OUTPUT_OVERRIDE,
	OUTPUT_APPEND
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
	struct s_assign			assign;
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
t_node						*new_assign_node(char *var, char *value);
t_node						*new_pipe_node(t_node *left, t_node *right);
t_node						*new_cmd_node(char **args, t_redirection redirs[2]);
t_node						*new_string_node(char *string);
