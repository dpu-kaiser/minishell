/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 15:06:25 by dkaiser           #+#    #+#             */
/*   Updated: 2024/08/02 14:10:31 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

static char	**collect_args(t_token **tokens);

t_node	*parse_cmd(t_token *tokens)
{
	char			**args;
	t_assign		**assigns;
	t_redirection	*redirs;

	redirs = collect_redirs(&tokens);
	assigns = collect_assigns(&tokens);
	args = collect_args(&tokens);
	return (new_cmd_node(args, assigns, redirs));
}

static char	**collect_args(t_token **tokens)
{
	t_token	*cur;
	char	**result;
	int		i;

	cur = *tokens;
	i = 0;
	while (cur != NULL)
	{
		i++;
		cur = cur->next;
	}
	result = malloc(sizeof(char *) * (i + 1));
	if (!result)
	{
		free_tokens(*tokens);
		return (NULL);
	}
	cur = *tokens;
	i = 0;
	while (cur != NULL && cur->type == STRING_TOKEN)
	{
		result[i] = cur->content.string;
		i++;
		cur = cur->next;
		free_token(cur->previous);
	}
	result[i] = NULL;
	return (result);
}
