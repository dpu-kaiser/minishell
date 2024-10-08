/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:27:18 by dkaiser           #+#    #+#             */
/*   Updated: 2024/08/11 13:46:22 by chuhlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "stdlib.h"

enum						e_token_type
{
	STRING_TOKEN,
	PIPE_TOKEN,
	REDIR_TOKEN,
	NEWLINE_TOKEN
};

union						u_token_content
{
	char					*string;
	int						redir_type;
};

typedef struct s_token
{
	int						type;
	union u_token_content	content;
	struct s_token			*previous;
	struct s_token			*next;
}							t_token;

t_token						*new_token(int type, t_token *previous,
								t_token *next);
t_token						*new_str_token(char *str, t_token *previous,
								t_token *next);
t_token						*new_redir_token(int type, t_token *previous,
								t_token *next);

void						free_token(t_token *token);
void						tokenizer(char *s, t_token **token_list,
								char quote_check);

#endif