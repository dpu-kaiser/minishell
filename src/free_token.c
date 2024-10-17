/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:38:57 by dkaiser           #+#    #+#             */
/*   Updated: 2024/08/02 14:23:56 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

void	free_token(t_token *token)
{
	if (token->previous != NULL)
		token->previous->next = NULL;
	if (token->next != NULL)
		token->next->previous = NULL;
	free(token);
}

void	free_token_and_connect(t_token *token)
{
	if (token->previous != NULL)
		token->previous->next = token->next;
	if (token->next != NULL)
		token->next->previous = token->previous;
	free(token);
}

void	free_tokens(t_token *tokens)
{
	while (tokens->next != NULL)
	{
		tokens = tokens->next;
		free_token(tokens->previous);
	}
	free_token(tokens);
}
