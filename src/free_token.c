/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:38:57 by dkaiser           #+#    #+#             */
/*   Updated: 2024/08/30 17:48:33 by chuhlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

// void	free_token(t_token *token)
// {
// 	if (token->type == STRING_TOKEN)
// 		free(token->content.string);
// 	if (token->previous != NULL)
// 		token->previous->next = NULL;
// 	if (token->next != NULL)
// 		token->next->previous = NULL;
// 	free(token);
// }

void	free_token_list(t_token **t_list)//&tokelist
{
	t_token	*positionold;
	t_token	*positionnew;

	if (!t_list)
		return ;
	positionold = *t_list;
	while (positionold)
	{
		positionnew = positionold->next;
		if (positionold->type == STRING_TOKEN)
			free(positionold->content.string);
		free (positionold);
		positionold = positionnew;
	}
	t_list = NULL;
}