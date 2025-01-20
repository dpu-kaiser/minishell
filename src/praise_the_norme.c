/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   praise_the_norme.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:35:41 by dkaiser           #+#    #+#             */
/*   Updated: 2025/01/20 18:39:31 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	i_love_the_norme(t_token **cur, t_token **tokens)
{
	t_token	*next_token;

	next_token = (*cur)->next;
	free_token_and_connect(*cur);
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
