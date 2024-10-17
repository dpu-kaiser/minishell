/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_redirs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 13:49:31 by dkaiser           #+#    #+#             */
/*   Updated: 2024/09/17 19:48:48 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*collect_redir(t_token **tokens, t_redirection *result,
					t_token *cur);
static void		collect_and_check_redir(t_token **tokens, t_redirection *result,
					t_token **cur);
static void		set_redir(t_redirection *redir, int type, char *specifier);
static int		is_output_redir(int i);

t_redirection	*collect_redirs(t_token **tokens)
{
	t_redirection	*result;
	t_token			*cur;

	cur = *tokens;
	result = malloc(sizeof(t_redirection) * 2);
	if (result == NULL)
		return (free_tokens(*tokens), NULL);
	set_redir(&result[0], 0, NULL);
	set_redir(&result[1], 0, NULL);
	while (cur != NULL && cur->next != NULL)
	{
		if (cur->type == REDIR_TOKEN && cur->next->type == STRING_TOKEN)
			collect_and_check_redir(tokens, result, &cur);
		else if (cur->type == REDIR_TOKEN)
			return (free(result), NULL);
		else
			cur = cur->next;
	}
	if (cur && cur->type == REDIR_TOKEN)
		return (free(result), NULL);
	return (result);
}

static void	collect_and_check_redir(t_token **tokens, t_redirection *result,
		t_token **cur)
{
	int	is_redir_only;

	is_redir_only = 0;
	if ((*cur)->previous == NULL && (*cur)->next->next == NULL)
		is_redir_only = 1;
	*cur = collect_redir(tokens, result, *cur);
	if (is_redir_only)
		*tokens = NULL;
}

static t_token	*collect_redir(t_token **tokens, t_redirection *result,
		t_token *cur)
{
	set_redir(&result[is_output_redir(cur->content.redir_type)],
		cur->content.redir_type, cur->next->content.string);
	cur = cur->next;
	free_token_and_connect(cur->previous);
	if (cur->next != NULL)
	{
		if (cur->previous == NULL)
			*tokens = cur->next;
		cur = cur->next;
		free_token_and_connect(cur->previous);
	}
	else
	{
		free_token(cur);
		return (NULL);
	}
	return (cur);
}

static void	set_redir(t_redirection *redir, int type, char *specifier)
{
	redir->type = type;
	redir->specifier = specifier;
}

static int	is_output_redir(int i)
{
	if (i & (INPUT_FILE | INPUT_LIMITER))
		return (0);
	else if (i & (OUTPUT_APPEND | OUTPUT_OVERRIDE))
		return (1);
	else
	{
		panic(UNREACHABLE);
		return (-1);
	}
}
