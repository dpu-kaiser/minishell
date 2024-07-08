/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:53:29 by dkaiser           #+#    #+#             */
/*   Updated: 2024/07/08 16:11:07 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*find_token_by_type(t_token *tokens, int type);
t_token			*split_at_first(t_token **tokens, int type);

static t_node	*parse_statement(t_token *tokens);
static t_node	*parse_cmd(t_token *tokens);

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
		{
			// Free: ft_lstclear(&result, free_node);
			return (NULL);
		}
		current_tokens = split_at_first(&tokens, NEWLINE_TOKEN);
	}
	return (result);
}

static t_node	*parse_statement(t_token *tokens)
{
	t_token	*left_side_tokens;

	left_side_tokens = split_at_first(&tokens, PIPE_TOKEN);
	if (tokens != NULL)
	{
		return (new_pipe_node(parse_cmd(left_side_tokens),
				parse_statement(tokens)));
	}
	else
	{
		return (parse_cmd(left_side_tokens));
	}
}

static t_node	*parse_cmd(t_token *tokens)
{
	char			**args;
	t_assign		**assigns;
	t_redirection	**redirs;

	redirs = collect_redirs(&tokens);
	assigns = collect_assigns(&tokens);
	args = collect_args(&tokens);
	return (new_cmd_node(args, assigns, redirs));
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
