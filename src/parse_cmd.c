/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 15:06:25 by dkaiser           #+#    #+#             */
/*   Updated: 2024/08/11 12:20:06 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**collect_args(t_token **tokens);

t_node	*parse_cmd(t_token *tokens)
{
	char			**args;
	t_redirection	*redirs;

	redirs = collect_redirs(&tokens);
	args = collect_args(&tokens);
	return (new_cmd_node(args, redirs));
}

static char	**collect_args(t_token **tokens)
{
	t_token	*cur;
	char	**result;
	int		i;

	cur = *tokens;
	i = 0;
	while (cur != NULL && ++i)
		cur = cur->next;
	result = malloc(sizeof(char *) * (i + 1));
	if (result == NULL)
		return (free_tokens(*tokens), NULL);
	cur = *tokens;
	i = 0;
	while (cur != NULL && cur->type == STRING_TOKEN)
	{
		if (cur->previous)
			free_token(cur->previous);
		result[i] = cur->content.string;
		i++;
		cur = cur->next;
	}
	result[i] = NULL;
	return (result);
}
