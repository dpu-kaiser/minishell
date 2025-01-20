/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_redirs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 13:49:31 by dkaiser           #+#    #+#             */
/*   Updated: 2025/01/20 13:00:04 by chuhlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static void				collect_and_check_redir(t_redirection *result,
							t_token **cur, t_env *env, t_list **create_files);
static t_redirection	*set_redir(t_redirection *redir, int type, char *spec,
							t_env *env);
static int				set_heredoc_data(t_token *cur, t_redirection *result,
							t_env *env);

t_redirection	*collect_redirs(t_token **tokens, t_env *env,
	t_list **create_files)
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
			collect_and_check_redir(result, &cur, env, create_files);
		else if (cur->type == REDIR_TOKEN)
			return (free(result), NULL);
		else
			cur = cur->next;
	}
	if (cur && cur->type == REDIR_TOKEN)
		return (free(result), NULL);
	return (result);
}

static void	collect_and_check_redir(t_redirection *result, t_token **cur,
		t_env *env, t_list **create_files)
{
	t_token	*next_token;
	char	*str;

	if ((*cur)->content.redir_type != INPUT_LIMITER)
		str = ft_strdup((*cur)->next->content.string);
	if ((*cur)->content.redir_type == INPUT_LIMITER)
	{
		if (!set_heredoc_data(*cur, result, env))
			return ;
	}
	else if ((*cur)->content.redir_type == INPUT_FILE)
		set_redir(&result[0], INPUT_FILE, str, env);
	else if ((*cur)->content.redir_type == OUTPUT_OVERRIDE)
		ft_lstadd_back(create_files, ft_lstnew(set_redir(&result[1],
					OUTPUT_OVERRIDE, str, env)));
	else if ((*cur)->content.redir_type == OUTPUT_APPEND)
		ft_lstadd_back(create_files, ft_lstnew(set_redir(&result[1],
					OUTPUT_APPEND, str, env)));
	next_token = (*cur)->next;
	// free_token_and_connect(*cur);
	if (next_token)
	{
		*cur = next_token->next;
		free_token_and_connect(next_token);
	}
	else
		*cur = NULL;
}

static t_redirection	*set_redir(t_redirection *redir, int type, char *spec,
		t_env *env)
{
	t_redirection	*result;

	redir->type = type;
	if (spec != NULL)
		redir->specifier = format_string(spec, env, ft_atoi("0"));
	else
		redir->specifier = spec;
	if (redir->type == OUTPUT_APPEND || redir->type == OUTPUT_OVERRIDE)
	{
		result = malloc(sizeof(t_redirection));
		if (!result)
			return (NULL);
		result->type = type;
		result->specifier = spec;
		return (result);
	}
	return (NULL);
}



static int	set_heredoc_data(t_token *cur, t_redirection *result, t_env *env)
{
	char	*heredoc_data;

	heredoc_data = NULL;
	if (cur->content.redir_type == INPUT_LIMITER)
	{
		heredoc_data = read_heredoc(cur->next->content.string);
		if (!heredoc_data)
		{
			perror("Heredoc allocation failed");
			return (0);
		}
		set_redir(&result[0], INPUT_LIMITER, heredoc_data, env);
	}
	set_redir(&result[0], INPUT_LIMITER, heredoc_data, env);
	return (1);
}
