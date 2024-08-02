/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_redirs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 13:49:31 by dkaiser           #+#    #+#             */
/*   Updated: 2024/08/02 13:52:48 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		set_redir(t_redirection *redir, int type, char *specifier);

t_redirection	*collect_redirs(t_token **tokens)
{
	t_redirection	*result;
	t_token			*cur;
	int				idx;

	cur = *tokens;
	result = malloc(sizeof(t_redirection) * 2);
	if (result == NULL)
	{
		// free all tokens
		return (NULL);
	}
	set_redir(&result[0], 0, NULL);
	set_redir(&result[1], 0, NULL);
	while (cur != NULL && cur->next != NULL)
	{
		if (cur->type == REDIR_TOKEN && cur->next->type == STRING_TOKEN)
		{
			if (cur->content.redir_type & (INPUT_FILE | INPUT_LIMITER))
				idx = 0;
			else if (cur->content.redir_type & (OUTPUT_APPEND | OUTPUT_OVERRIDE))
				idx = 1;
			set_redir(&result[idx], cur->content.redir_type,
				cur->next->content.string);
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
			}
		}
		else if (cur->type == REDIR_TOKEN)
		{
			// err Parsing error
			free(result);
			return (NULL);
		}
		else
		{
			cur = cur->next;
		}
	}
	return (result);
}

static void	set_redir(t_redirection *redir, int type, char *specifier)
{
	redir->type = type;
	redir->specifier = specifier;
}
