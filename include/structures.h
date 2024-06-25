/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:26:40 by dkaiser           #+#    #+#             */
/*   Updated: 2024/06/25 17:34:51 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

enum							e_token_type
{
	PIPE,
	STRING,
	REDIRECT_IN,
	REDIRECT_OUT
};

enum							e_ast_type
{
	PIPELINE,
	CMD,
	STRING_LITERAL,
	FSTRING
};

typedef struct s_token
{
	int							type;
	char						*content;
	struct s_token				*previous;
	struct s_token				*next;
}								t_token;

typedef struct s_ast_node
{
	int							type;
	union u_ast_node_content	*content;
}								t_ast_node;

union							u_ast_node_content
{
	struct s_ast_node			*children;
	struct s_cmd				*cmd;
	struct s_fstring			*fstr;
	char						*str;
};

typedef struct s_cmd
{
	char						**args;
	char						*redirections[2];
}								t_cmd;

typedef struct s_fstring
{
	char						*fmt;
	char						**vars;
}								t_fstring;

#endif
