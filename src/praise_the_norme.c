/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   praise_the_norme.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:35:41 by dkaiser           #+#    #+#             */
/*   Updated: 2025/01/23 18:31:49 by chuhlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	i_love_the_norme(t_token **cur, t_token **tokens)
{
	t_token	*next_token;

	next_token = (*cur)->next;//setting next token to the adress of the next token
	free_token_and_connect(*cur);// do i neee a double call here
	//but technically it would remove the redir token
	if (next_token)// if after redir is stuff
	{
		if (next_token->previous == NULL)// then if is the first token or token after pipe
			*tokens = next_token->next;// how does here come no error
			//anyways i twould the redir adress token to the next token 
		*cur = next_token->next;
		free_token_and_connect(next_token);
	}
	else // else makes sense
		*cur = NULL;
}

// takes adress of token head or pos after pipe and the token specifer