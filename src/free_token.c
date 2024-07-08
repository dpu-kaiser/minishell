/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:38:57 by dkaiser           #+#    #+#             */
/*   Updated: 2024/07/08 14:48:18 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

void	free_token(t_token *token)
{
	if (token->type == STRING_TOKEN)
		free(token->content.string);
	if (token->previous != NULL)
		token->previous->next = NULL;
	if (token->next != NULL)
		token->next->previous = NULL;
	free(token);
}

void	free_token_and_connect(t_token *token)
{
	if (token->type == STRING_TOKEN)
		free(token->content.string);
	if (token->previous != NULL)
		token->previous->next = token->next;
	if (token->next != NULL)
		token->next->previous = token->previous;
	free(token);
}
