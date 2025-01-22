/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:53:29 by dkaiser           #+#    #+#             */
/*   Updated: 2025/01/22 17:13:50 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "token.h"
#include "env.h"

static t_token	*find_token_by_type(t_token *tokens, int type);
t_token			*split_at_first(t_token **tokens, int type);
static t_node	*parse_statement(t_token *tokens, t_env **env);

t_node	*parse(t_token *tokens, t_env **env)
{
	t_node	*result;

	if ((*tokens).type == PIPE_TOKEN)
		result = NULL;
	else
		result = parse_statement(tokens, env);
	if (result == NULL)
		printf("Parsing error.\n");
	return (result);
}

static t_node	*parse_statement(t_token *tokens, t_env **env)
{
	t_token	*left_side_tokens;

	left_side_tokens = split_at_first(&tokens, PIPE_TOKEN);
	if (left_side_tokens == NULL)
	{
		free_tokens(tokens);
		tokens = NULL;
		return (NULL);
	}
	else if (tokens != NULL)
	{
		return (new_pipe_node(parse_cmd(left_side_tokens, env),
				parse_statement(tokens, env)));
	}
	else
	{
		return (parse_cmd(left_side_tokens, env));
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
	free_token2(split);
	split = NULL;
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
