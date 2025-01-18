/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 15:06:25 by dkaiser           #+#    #+#             */
/*   Updated: 2025/01/18 19:01:21 by chuhlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**collect_args(t_token **tokens, t_env **env);

t_node	*parse_cmd(t_token *tokens, t_env **env)
{
	char			**args;
	t_redirection	*redirs;

	redirs = collect_redirs(&tokens, *env);
	if (redirs == NULL)
		return (NULL);
	args = collect_args(&tokens, env);
	if (args == NULL)
	{
		free(redirs);
		return (NULL);
	}
	return (new_cmd_node(args, redirs));
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
		result[i] = format_string(cur->content.string, *env, ft_atoi("0"));
		i++;
		cur = cur->next;
	}
	result[i] = NULL;
	return (result);
}
