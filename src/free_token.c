/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:38:57 by dkaiser           #+#    #+#             */
/*   Updated: 2025/01/22 00:07:58 by chuhlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "debug_tools.h"

void	free_token(t_token *token)
{
	if (token->previous != NULL)
		token->previous->next = NULL;
	if (token->next != NULL)
		token->next->previous = NULL;
    // if (token->type == STRING_TOKEN && token->content.string != NULL)
    //     free(token->content.string); // Ensure content is freed
	free(token);//maybe free token
	token = NULL;
}

void	free_token_and_connect(t_token *token)
{
	if (token->previous != NULL)
		token->previous->next = token->next;
	if (token->next != NULL)
		token->next->previous = token->previous;
	free(token);
	token = NULL;
}

// void	free_tokens(t_token *tokens)
// {
// 	while (tokens->next != NULL)
// 	{
// 		tokens = tokens->next;
// 		free_token(tokens->previous);
// 	}
// 	free_token(tokens);
// }
void free_tokens(t_token *tokens)
{
    t_token *tmp;

    while (tokens)
    {
        tmp = tokens;
        tokens = tokens->next;
        free_token(tmp); // Ensure each token is freed
    }
}
