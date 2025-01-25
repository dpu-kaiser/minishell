/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   praise_the_norme.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:35:41 by dkaiser           #+#    #+#             */
/*   Updated: 2025/01/25 11:34:26 by chuhlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	i_love_the_norme(t_token **cur, t_token **tokens)
{
	t_token	*next_token;

	next_token = (*cur)->next;
	free_token_and_connect2(*cur);
	if (next_token)
	{
		if (next_token->previous == NULL)
			*tokens = next_token->next;
		*cur = next_token->next;
		free_token_and_connect(next_token);
	}
	else
		*cur = NULL;
}
