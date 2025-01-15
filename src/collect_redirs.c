/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_redirs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 13:49:31 by dkaiser           #+#    #+#             */
/*   Updated: 2025/01/15 18:10:46 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		collect_and_check_redir(t_redirection *result, t_token **cur,
					t_env *env);
static void		set_redir(t_redirection *redir, int type, char *specifier,
					t_env *env);

static char	*read_heredoc(char *delimiter)
{
	char	*line;
	char	*result;
	char	*temp;
	size_t	total_length;
	size_t	line_length;

	total_length = 0;
	result = NULL;
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		line_length = ft_strlen(line) + 1;
		temp = malloc(total_length + line_length + 1);
		if (!temp)
		{
			perror("malloc");
			return (free(result), NULL);
		}
		if (result)
		{
			ft_strcpy(temp, result);
			free(result);
		}
		else
			temp[0] = '\0';
		ft_strcat(temp, line);
		ft_strcat(temp, "\n");
		result = temp;
		total_length += line_length;
		free(line);
	}
	return (result);
}

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

static void	set_redir(t_redirection *redir, int type, char *specifier,
		t_env *env)
{
	redir->type = type;
	if (specifier != NULL)
		redir->specifier = format_string(specifier, env);
	else
		redir->specifier = specifier;
}

static void	collect_and_check_redir(t_redirection *result, t_token **cur,
		t_env *env)
{
	char	*heredoc_data;
	t_token	*next_token;

	heredoc_data = NULL;
	if ((*cur)->content.redir_type == INPUT_LIMITER)
	{
		heredoc_data = read_heredoc((*cur)->next->content.string);
		if (!heredoc_data)
		{
			perror("Heredoc allocation failed");
			return ;
		}
		set_redir(&result[0], INPUT_LIMITER, heredoc_data, env);
	}
	else if ((*cur)->content.redir_type == INPUT_FILE)
		set_redir(&result[0], INPUT_FILE,
			ft_strdup((*cur)->next->content.string), env);
	else if ((*cur)->content.redir_type == OUTPUT_OVERRIDE)
		set_redir(&result[1], OUTPUT_OVERRIDE,
			ft_strdup((*cur)->next->content.string), env);
	else if ((*cur)->content.redir_type == OUTPUT_APPEND)
		set_redir(&result[1], OUTPUT_APPEND,
			ft_strdup((*cur)->next->content.string), env);
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
