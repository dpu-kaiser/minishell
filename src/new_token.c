/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:29:44 by dkaiser           #+#    #+#             */
/*   Updated: 2024/08/29 15:30:52 by chuhlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

t_token	*new_token(int type, t_token *previous, t_token *next)
{
	t_token	*token;

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

t_token	*new_str_token(char *str, t_token *previous, t_token *next)
{
	t_token	*token;

	token = new_token(STRING_TOKEN, previous, next);
	if (token == NULL)
		return (NULL);
	token->content.string = str;
	return (token);
}

t_token	*new_redir_token(int type, t_token *previous, t_token *next)
{
	t_token	*token;

	token = new_token(REDIR_TOKEN, previous, next);
	if (token == NULL)
		return (NULL);
	token->content.redir_type = type;
	return (token);
}

// void	ft_append_token(int type, t_token **list)// but we need somewhere token/node head initialize with nul
// {
// 	t_token	*node;
// 	t_token	*last_node;

// 	if (!list)
// 		return ;
// 	node = malloc(sizeof(t_token));
// 	if (!node)
// 		return ;
// 	node->next = NULL;
// 	node->type = type;
// 	if (!*list)
// 	{
// 		*list = node;
// 		node->previous = NULL;
// 	}
// 	else
// 	{
// 		last_node = ft_lstlast(*list);
// 		last_node->next = node;
// 		node->previous = last_node;
// 	}
// }