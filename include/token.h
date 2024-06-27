/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:27:18 by dkaiser           #+#    #+#             */
/*   Updated: 2024/06/27 14:28:46 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
#define TOKEN_H

enum e_token_type
{
STRING,
PIPE,
REDIR,
NEWLINE
};

union u_token_content
{
    char *string;
    int redir_type;
};

typedef struct s_token
{
    int type;
    union u_token_content content;
    struct s_token *previous;
    struct s_token *next;
} t_token;

#endif
