/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_redirs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 13:49:31 by dkaiser           #+#    #+#             */
/*   Updated: 2025/01/11 11:43:13 by chuhlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static t_token	*collect_redir(t_token **tokens, t_redirection *result,
// 					t_token *cur);
// static void		collect_and_check_redir(t_token **tokens, t_redirection *result,
// 					t_token **cur);
static void		collect_and_check_redir(t_redirection *result, t_token **cur);
static void		set_redir(t_redirection *redir, int type, char *specifier);
// static int		is_output_redir(int i);

// static char	*read_heredoc(char *delimiter)
// {
// 	char	*line;
// 	char	*result;
// 	size_t	len;

// 	result = NULL;
// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (!line || ft_strcmp(line, delimiter) == 0)
// 		{
// 			free(line);
// 			break ;
// 		}
// 		if (result)
// 			len = ft_strlen(result);
// 		else
// 			len = 0;
// 		result = realloc(result, len + ft_strlen(line) + 2);
// 		if (!result)
// 			return (NULL);
// 		ft_strcpy(result + len, line);
// 		strcat(result, "\n");
// 		free(line);
// 	}
// 	return (result);
// }

//v2.0

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
			free(result);
			return (NULL);
		}
		if (result)
		{
			ft_strcpy(temp, result);
			free(result);
		}
		else
		{
			temp[0] = '\0';
		}
		ft_strcat(temp, line);
		ft_strcat(temp, "\n");
		result = temp;
		total_length += line_length;
		free(line);
	}
	return (result);
}

t_redirection	*collect_redirs(t_token **tokens)
{
	t_redirection	*result;
	t_token			*cur;

	cur = *tokens;
	result = malloc(sizeof(t_redirection) * 2);
	if (result == NULL)
		return (free_tokens(*tokens), NULL);
	set_redir(&result[0], 0, NULL);
	set_redir(&result[1], 0, NULL);
	while (cur != NULL && cur->next != NULL)
	{
		if (cur->type == REDIR_TOKEN && cur->next->type == STRING_TOKEN)
			collect_and_check_redir(result, &cur);// her is diff
		else if (cur->type == REDIR_TOKEN)
			return (free(result), NULL);
		else
			cur = cur->next;
	}
	if (cur && cur->type == REDIR_TOKEN)
		return (free(result), NULL);
	return (result);
}

// static void	collect_and_check_redir(t_token **tokens, t_redirection *result,
// 		t_token **cur)
// {
// 	int	is_redir_only;

// 	is_redir_only = 0;
// 	if ((*cur)->previous == NULL && (*cur)->next->next == NULL)
// 		is_redir_only = 1;
// 	*cur = collect_redir(tokens, result, *cur);
// 	if (is_redir_only)
// 		*tokens = NULL;
// }

// static t_token	*collect_redir(t_token **tokens, t_redirection *result,
// 		t_token *cur)
// {
// 	set_redir(&result[is_output_redir(cur->content.redir_type)],
// 		cur->content.redir_type, cur->next->content.string);
// 	cur = cur->next;
// 	free_token_and_connect(cur->previous);
// 	if (cur->next != NULL)
// 	{
// 		if (cur->previous == NULL)
// 			*tokens = cur->next;
// 		cur = cur->next;
// 		free_token_and_connect(cur->previous);
// 	}
// 	else
// 	{
// 		free_token(cur);
// 		return (NULL);
// 	}
// 	return (cur);
// }

static void	set_redir(t_redirection *redir, int type, char *specifier)
{
	redir->type = type;
	redir->specifier = specifier;
}

// static int	is_output_redir(int i)
// {
// 	if (i & (INPUT_FILE | INPUT_LIMITER))
// 		return (0);
// 	else if (i & (OUTPUT_APPEND | OUTPUT_OVERRIDE))
// 		return (1);
// 	else
// 	{
// 		panic(UNREACHABLE);
// 		return (-1);
// 	}
// }

//2.0

static void	collect_and_check_redir(t_redirection *result, t_token **cur)
{
	char	*heredoc_data;
	t_token	*next_token;

	heredoc_data = NULL;
	if ((*cur)->content.redir_type == INPUT_LIMITER)
	{
		// Handle Here Document (<<)
		heredoc_data = read_heredoc((*cur)->next->content.string);
		if (!heredoc_data)
		{
			perror("Heredoc allocation failed");
			return ;
		}
		set_redir(&result[0], INPUT_LIMITER, heredoc_data);
	}
	else if ((*cur)->content.redir_type == INPUT_FILE)
	{
		// Handle Input File (<)
		set_redir(&result[0], INPUT_FILE, ft_strdup((*cur)->next->content.string));
	}
	else if ((*cur)->content.redir_type == OUTPUT_OVERRIDE)
	{
		// Handle Output File Overwrite (>)
		set_redir(&result[1], OUTPUT_OVERRIDE, ft_strdup((*cur)->next->content.string));
	}
	else if ((*cur)->content.redir_type == OUTPUT_APPEND)
	{
		// Handle Output File Append (>>)
		set_redir(&result[1], OUTPUT_APPEND, ft_strdup((*cur)->next->content.string));
	}
	else
	{
		// Handle unexpected cases
		printf("Unknown redirection type encountered\n");
	}
    // Advance the token pointer to skip the redirection token and its argument
	next_token = (*cur)->next;
	free_token_and_connect(*cur);  // Free the current redirection token
	if (next_token)
	{
		*cur = next_token->next;   // Move to the next token after the argument
		free_token_and_connect(next_token);  // Free the argument token
	}
	else
	{
		*cur = NULL;  // No more tokens
	}
}