/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_redirs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 13:49:31 by dkaiser           #+#    #+#             */
/*   Updated: 2025/01/25 14:37:06 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static void				collect_and_check_redir(t_redirection *result,
							t_token **cur, t_minidata *data, t_token **tokens);
static t_redirection	*set_redir(t_redirection *redir, int type, char *spec,
							t_env *env);
static int				set_heredoc_data(t_token *cur, t_redirection *result,
							t_env *env);

t_redirection	*collect_redirs(t_token **tokens, t_env *env,
		t_list **create_files)
{
	t_redirection	*result;
	t_token			*cur;
	t_minidata		data;

	cur = *tokens;
	result = malloc(sizeof(t_redirection) * 2);
	if (result == NULL)
		return (free_tokens(*tokens), NULL);
	free(set_redir(&result[0], 0, NULL, env));
	free(set_redir(&result[1], 0, NULL, env));
	data.create_files = create_files;
	data.env = env;
	while (cur != NULL)
	{
		if (cur->type == REDIR_TOKEN && cur->next->type == STRING_TOKEN)
			collect_and_check_redir(result, &cur, &data, tokens);
		else if (cur->type == REDIR_TOKEN)
			return (free(result), NULL);
		else
			cur = cur->next;
	}
	return (result);
}

static void	collect_and_check_redir(t_redirection *result, t_token **cur,
		t_minidata *data, t_token **tokens)
{
	char	*str;

	if ((*cur)->content.redir_type != INPUT_LIMITER)
		str = (*cur)->next->content.string;
	if ((*cur)->content.redir_type == INPUT_LIMITER)
	{
		if (!set_heredoc_data(*cur, result, data->env))
			return ;
	}
	else if ((*cur)->content.redir_type == INPUT_FILE)
		q4fc(data->create_files, set_redir(&result[0], INPUT_FILE,
				format_string(str, data->env, 0), data->env));
	else if ((*cur)->content.redir_type == OUTPUT_OVERRIDE)
		q4fc(data->create_files, set_redir(&result[1], OUTPUT_OVERRIDE,
				format_string(str, data->env, 0), data->env));
	else if ((*cur)->content.redir_type == OUTPUT_APPEND)
		q4fc(data->create_files, set_redir(&result[1], OUTPUT_APPEND,
				format_string(str, data->env, 0), data->env));
	i_love_the_norme(cur, tokens);
	free(str);
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
	if (redir->type != INPUT_LIMITER)
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
