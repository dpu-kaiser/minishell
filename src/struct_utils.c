/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:38:16 by dkaiser           #+#    #+#             */
/*   Updated: 2024/06/25 17:48:09 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include <stdlib.h>

t_token	*new_token(int type, char *content)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (new == NULL)
		return (NULL);
	new->type = type;
	new->content = content;
	return (new);
}

void	delete_token(t_token *token)
{
	if (token->content)
		free(token->content);
	if (token->previous)
		token->previous->next = NULL;
	if (token->next)
		token->next->previous = NULL;
	free(token);
}
