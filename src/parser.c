/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:53:29 by dkaiser           #+#    #+#             */
/*   Updated: 2025/01/23 18:00:18 by chuhlig          ###   ########.fr       */
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
	t_node	*result;//

	if ((*tokens).type == PIPE_TOKEN)
		result = NULL;
	else
		result = parse_statement(tokens, env);
	if (result == NULL)
		printf("Parsing error.\n");
	// if (tokens != NULL)
	// 	print_token_list(tokens);
	return (result);
}

static t_node	*parse_statement(t_token *tokens, t_env **env)
{
	t_token	*left_side_tokens;
	
	print_token_list(tokens);//until her is fine
	left_side_tokens = split_at_first(&tokens, PIPE_TOKEN);//by pipe usage parse cmd gets reacls so also check there the token list changes
	//leftside toke has the pos of pipe -> next
	//or if we have pipe we return token head and also change the *tokens to after pipe
	if (left_side_tokens == NULL)// we never return NULL exept token is already null
	{
		free_tokens(tokens);
		tokens = NULL;
		return (NULL);
	}
	else if (tokens != NULL)
	{
		return (new_pipe_node(parse_cmd(left_side_tokens, env),
				parse_statement(tokens, env)));//here new pipe node
	}
	else
	{
		print_token_list(left_side_tokens);
		return (parse_cmd(left_side_tokens, env));//here return is cmd node
	}// here he takt left side token so
}

t_token	*split_at_first(t_token **tokens, int type)
{
	t_token	*split;
	t_token	*result;

	split = find_token_by_type(*tokens, type);//split has the pos of where pipe appears// if no pipe in tokenlist 1st if case
	if (split == NULL)
	{
		result = *tokens;
		*tokens = NULL;//we are change to pointing token to NULL
		return (result);
	}
	result = *tokens;
	*tokens = split->next;// is this part enought reconnetion
	if (result == split)
		result = NULL;
	free_token2(split);//why free here? bv would free pipe node but what is with the connection of the tokenlist does this mess up the connection?
	split = NULL;
	return (result);// at this return return is at tokenlist pos of split next and result is the tokenlist before split
}
//free token seems not right here even 
// or at least no the right funtion here 
// 

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
