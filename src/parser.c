/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:53:29 by dkaiser           #+#    #+#             */
/*   Updated: 2024/09/17 15:06:55 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

static t_token	*find_token_by_type(t_token *tokens, int type);
t_token			*split_at_first(t_token **tokens, int type);
static t_node	*parse_statement(t_token *tokens);
static void		free_node_wrapper(void *node);

t_list	*parse(t_token *tokens)
{
	t_list	*result;
	t_list	*current;
	t_token	*current_tokens;

	result = NULL;
	current_tokens = split_at_first(&tokens, NEWLINE_TOKEN);
	while (current_tokens != NULL)
	{
		if (result == NULL)
		{
			current = ft_lstnew(parse_statement(current_tokens));
			result = current;
		}
		else
		{
			current->next = ft_lstnew(parse_statement(current_tokens));
			current = current->next;
		}
		if (current == NULL)
			return (ft_lstclear(&result, free_node_wrapper), NULL);
		current_tokens = split_at_first(&tokens, NEWLINE_TOKEN);
	}
	return (result);
}

static t_node	*parse_statement(t_token *tokens)
{
	t_token	*left_side_tokens;

	left_side_tokens = split_at_first(&tokens, PIPE_TOKEN);
	if (left_side_tokens == NULL)
	{
		free_tokens(tokens);
		printf("Parsing error.\n");
		return (NULL);
	}
	else if (tokens != NULL)
	{
		return (new_pipe_node(parse_cmd(left_side_tokens),
				parse_statement(tokens)));
	}
	else
	{
		return (parse_cmd(left_side_tokens));
	}
}

t_token	*split_at_first(t_token **tokens, int type)
{
	t_token	*split;
	t_token	*result;

	split = find_token_by_type(*tokens, type);
	if (split == NULL)
	{
		result = *tokens;
		*tokens = NULL;
		return (result);
	}
	result = *tokens;
	*tokens = split->next;
	if (result == split)
		result = NULL;
	free_token(split);
	return (result);
}

static t_token	*find_token_by_type(t_token *tokens, int type)
{
	while (tokens != NULL)
	{
		if (tokens->type == type)
			return (tokens);
		tokens = tokens->next;
	}
	return (NULL);
}

static void	free_node_wrapper(void *node)
{
	free_node((t_node *)node);
}
