/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 15:06:25 by dkaiser           #+#    #+#             */
/*   Updated: 2025/01/25 15:00:55 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**collect_args(t_token **tokens, t_env **env);
static void	setup_vars(t_token **tokens, t_token **cur, int *i);

t_node	*parse_cmd(t_token *tokens, t_env **env)
{
	char			**args;
	t_redirection	*redirs;
	t_list			*create_files;

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
	t_token	*next;

	setup_vars(tokens, &cur, &i);
	while (cur != NULL && ++i)
		cur = cur->next;
	result = malloc(sizeof(char *) * (i + 1));
	if (result == NULL)
		return (free_tokens(*tokens), NULL);
	setup_vars(tokens, &cur, &i);
	while (cur != NULL && cur->type == STRING_TOKEN)
	{
		next = cur->next;
		if (cur->previous)
			free_token2(cur->previous);
		result[i++] = format_string(cur->content.string, *env, ft_atoi("0"));
		if (cur->next == NULL)
			free_token2(cur);
		cur = next;
	}
	result[i] = NULL;
	return (result);
}

static void	setup_vars(t_token **tokens, t_token **cur, int *i)
{
	*cur = *tokens;
	*i = 0;
}
