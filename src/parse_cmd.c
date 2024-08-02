/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 15:06:25 by dkaiser           #+#    #+#             */
/*   Updated: 2024/08/02 12:54:45 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug_tools.h"
#include "minishell.h"
#include "token.h"

static t_redirection	*collect_redirs(t_token **tokens);
static t_assign			**collect_assigns(t_token **tokens);
static char				**collect_args(t_token **tokens);
static t_assign			*to_assign(char *str);
static void				set_redir(t_redirection *redir, int type,
							char *specifier);

t_node	*parse_cmd(t_token *tokens)
{
	char			**args;
	t_assign		**assigns;
	t_redirection	*redirs;

	dbg("parse_cmd");
	redirs = collect_redirs(&tokens);
	t_token *cur;
	cur = tokens;
	while (cur != NULL && cur->type != 0) {
		print_token(cur);
		cur = cur->next;
	}


	assigns = collect_assigns(&tokens);


	args = collect_args(&tokens);
	dbg("ret parse_cmd");
	return (new_cmd_node(args, assigns, redirs));
}

static t_redirection	*collect_redirs(t_token **tokens)
{
	t_redirection	*result;
	t_token			*cur;
	int				idx;

	dbg("collect_redirs");
	cur = *tokens;
	result = malloc(sizeof(t_redirection) * 2);
	if (result == NULL)
	{
		// free all tokens
		return (NULL);
	}
	set_redir(&result[0], 0, NULL);
	set_redir(&result[1], 0, NULL);
	while (cur != NULL && cur->next != NULL)
	{
		if (cur->type == REDIR_TOKEN && cur->next->type == STRING_TOKEN)
		{
			if (cur->content.redir_type & (INPUT_FILE | INPUT_LIMITER))
				idx = 0;
			else if (cur->content.redir_type & (OUTPUT_APPEND | OUTPUT_OVERRIDE))
				idx = 1;
			set_redir(&result[idx], cur->content.redir_type,
				cur->next->content.string);
			cur = cur->next;
			free_token_and_connect(cur->previous);
			if (cur->next != NULL)
			{
				if (cur->previous == NULL)
					*tokens = cur->next;
				cur = cur->next;
				free_token_and_connect(cur->previous);
			}
			else
			{
				free_token(cur);
			}
		}
		else if (cur->type == REDIR_TOKEN)
		{
			// err Parsing error
			free(result);
			return (NULL);
		}
		else
		{
			cur = cur->next;
		}
	}
	return (result);
}

static t_assign	**collect_assigns(t_token **tokens)
{
	t_token		*cur;
	t_assign	**result;
	int			i;

	dbg("collect_assigns");
	cur = *tokens;
	i = 0;
	while (cur != NULL && cur->type == STRING_TOKEN
		&& cur->content.string[0] != '"' && cur->content.string[0] != '\''
		&& ft_strchr(cur->content.string, '=') != NULL)
	{
		i++;
		cur = cur->next;
	}
	result = malloc(sizeof(t_assign *) * (i + 1));
	if (!result)
	{
		// free all tokens
		return (NULL);
	}
	cur = *tokens;
	i = 0;
	while (cur != NULL && cur->type == STRING_TOKEN
		&& cur->content.string[0] != '"' && cur->content.string[0] != '\''
		&& ft_strchr(cur->content.string, '=') != NULL)
	{
		result[i] = to_assign(cur->content.string);
		i++;
		if (cur->next != NULL) {
			cur = cur->next;
			free_token(cur->previous);
		}
		else
		{
			free_token(cur);
		}
	}
	*tokens = cur;
	result[i] = NULL;
	return (result);
}

static t_assign	*to_assign(char *str)
{
	t_assign	*result;
	char		*split_pos;

	split_pos = ft_strchr(str, '=');
	*split_pos = '\0';
	result = malloc(sizeof(t_assign));
	if (result == NULL)
	{
		return (NULL);
	}
	result->var = str;
	result->value = split_pos + 1;
	return (result);
}

static char	**collect_args(t_token **tokens)
{
	t_token	*cur;
	char	**result;
	int		i;

	dbg("collect_args");
	cur = *tokens;
	i = 0;
	while (cur != NULL && cur->type == STRING_TOKEN)
	{
		i++;
		printf("%d\n", cur->type);
		cur = cur->next;
		dbg("end of loop");
	}
	result = malloc(sizeof(char *) * (i + 1));
	if (!result)
	{
		// free all tokens;
		return (NULL);
	}
	dbg("after malloc");
	cur = *tokens;
	i = 0;
	while (cur != NULL && cur->type == STRING_TOKEN)
	{
		result[i] = cur->content.string;
		// free token
		i++;
		cur = cur->next;
	}
	result[i] = NULL;
	dbg("ret collect_args");
	return (result);
}

static void	set_redir(t_redirection *redir, int type, char *specifier)
{
	redir->type = type;
	redir->specifier = specifier;
}
