/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:29:44 by dkaiser           #+#    #+#             */
/*   Updated: 2024/06/27 14:35:01 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

t_token new_token(int type, t_token *previous, t_token *next)
{
    t_token *token;

    token = malloc(sizeof(t_token));
    if (token == NULL)
        return (NULL);
    token->type = type;
    token->previous = previous;
    token->next = next;
    if (previous != NULL)
        token->previous->next = token;
    if (next != NULL)
        token->next->previous = token;
    return (token);
}

t_token new_str_token(char *str, t_token *previous, t_token *next)
{
    t_token *token;

    token = new_token(STRING, previous, next);
    if (token == NULL)
        return (NULL);
    token->content.string = str;
    return (token);
}

t_token new_redir_token(int redir_type, t_token *previous, t_token *next)
{
    token = new_token(REDIR, previous, next);
    if (token == NULL)
        return NULL;
    token->content.redir_type = redir_type;
    return (token);
}
