/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_redirs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 13:49:31 by dkaiser           #+#    #+#             */
/*   Updated: 2025/01/15 18:33:36 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		collect_and_check_redir(t_redirection *result, t_token **cur,
					t_env *env);
static void		set_redir(t_redirection *redir, int type, char *spec,
					t_env *env);
static char		*get_heredoc_data(t_token *cur);

t_redirection	*collect_redirs(t_token **tokens, t_env *env)
{
	t_redirection	*result;
	t_token			*cur;

	cur = *tokens;
	result = malloc(sizeof(t_redirection) * 2);
	if (result == NULL)
		return (free_tokens(*tokens), NULL);
	set_redir(&result[0], 0, NULL, env);
	set_redir(&result[1], 0, NULL, env);
	while (cur != NULL && cur->next != NULL)
	{
		if (cur->type == REDIR_TOKEN && cur->next->type == STRING_TOKEN)
			collect_and_check_redir(result, &cur, env);
		else if (cur->type == REDIR_TOKEN)
			return (free(result), NULL);
		else
			cur = cur->next;
	}
	if (cur && cur->type == REDIR_TOKEN)
		return (free(result), NULL);
	return (result);
}

static void	set_redir(t_redirection *redir, int type, char *spec, t_env *env)
{
	redir->type = type;
	if (spec != NULL)
		redir->specifier = format_string(spec, env);
	else
		redir->specifier = spec;
}

static void	collect_and_check_redir(t_redirection *result, t_token **cur,
		t_env *env)
{
	t_token	*next_token;
	char	*str;

	if ((*cur)->content.redir_type != INPUT_LIMITER)
		str = ft_strdup((*cur)->next->content.string);
	if ((*cur)->content.redir_type == INPUT_LIMITER)
	{
		set_redir(&result[0], INPUT_LIMITER, get_heredoc_data(*cur), env);
	}
	else if ((*cur)->content.redir_type == INPUT_FILE)
		set_redir(&result[0], INPUT_FILE, str, env);
	else if ((*cur)->content.redir_type == OUTPUT_OVERRIDE)
		set_redir(&result[1], OUTPUT_OVERRIDE, str, env);
	else if ((*cur)->content.redir_type == OUTPUT_APPEND)
		set_redir(&result[1], OUTPUT_APPEND, str, env);
	next_token = (*cur)->next;
	free_token_and_connect(*cur);
	if (next_token)
	{
		*cur = next_token->next;
		free_token_and_connect(next_token);
	}
	else
		*cur = NULL;
}

static char	*get_heredoc_data(t_token *cur)
{
	char	*heredoc_data;

	if (cur->content.redir_type == INPUT_LIMITER)
	{
		heredoc_data = read_heredoc(cur->next->content.string);
		if (!heredoc_data)
		{
			perror("Heredoc allocation failed");
			return ;
		}
		set_redir(&result[0], INPUT_LIMITER, heredoc_data, env);
	}
	return (heredoc_data);
}
