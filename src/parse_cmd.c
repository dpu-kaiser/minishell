/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 15:06:25 by dkaiser           #+#    #+#             */
/*   Updated: 2025/01/16 19:06:03 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**collect_args(t_token **tokens, t_env **env);

t_node	*parse_cmd(t_token *tokens, t_env **env)
{
	char			**args;
	t_redirection	*redirs;
	t_list *create_files;

	create_files = NULL;
	redirs = collect_redirs(&tokens, *env, &create_files);
	if (redirs == NULL)
		return (NULL);
	args = collect_args(&tokens, env);
	if (args == NULL)
	{
		free(redirs);
		return (NULL);
	}
	return (new_cmd_node(args, redirs, create_files));
}

static char	**collect_args(t_token **tokens, t_env **env)
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
		result[i] = format_string(cur->content.string, *env);
		i++;
		cur = cur->next;
	}
	result[i] = NULL;
	return (result);
}
