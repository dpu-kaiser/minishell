/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:27:18 by dkaiser           #+#    #+#             */
/*   Updated: 2024/07/22 17:11:15 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "stdlib.h"

enum						e_token_type
{
	STRING_TOKEN = 1,
	PIPE_TOKEN = 2,
	REDIR_TOKEN = 4,
	NEWLINE_TOKEN = 8
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
void						free_token_and_connect(t_token *token);

void						print_token(t_token *token);
void						conditional_print(char *string, int start_of_string, int i, int offset, t_token **token_list);
void						tokenizer(char *s, t_token **token_list);
void						print_token(t_token *token);


#endif
