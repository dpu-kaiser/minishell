/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:38:57 by dkaiser           #+#    #+#             */
/*   Updated: 2024/06/27 14:42:35 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

void free_token(t_token *token)
{
    if (token->type == STRING)
        free(token->content.string);
    if (token->previous != NULL)
        token->previous->next = NULL;
    if (token->next != NULL)
        token->next->previous = NULL;
    free(token);
}
