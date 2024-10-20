/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:53:29 by dkaiser           #+#    #+#             */
/*   Updated: 2024/09/17 19:03:48 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "token.h"

static t_token	*find_token_by_type(t_token *tokens, int type);
t_token			*split_at_first(t_token **tokens, int type);
static t_node	*parse_statement(t_token *tokens);

t_list	*parse(t_token *tokens)
{
	t_node	*result;

	if ((*tokens).type == PIPE_TOKEN)
		result = NULL;
	else
		result = parse_statement(tokens);
	if (result == NULL)
		printf("Parsing error.\n");
	return (ft_lstnew(result));
}

static t_node	*parse_statement(t_token *tokens)
{
	t_token	*left_side_tokens;

	left_side_tokens = split_at_first(&tokens, PIPE_TOKEN);
	if (left_side_tokens == NULL)
	{
		free_tokens(tokens);
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
