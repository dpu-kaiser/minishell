/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_assigns.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 13:54:36 by dkaiser           #+#    #+#             */
/*   Updated: 2024/08/02 14:37:41 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

static t_assign	*to_assign(char *str);
static int		count_tokens(t_token *tokens);
static int		is_quote(char c);

t_assign	**collect_assigns(t_token **tokens)
{
	t_token		*cur;
	t_assign	**result;
	int			i;

	result = malloc(sizeof(t_assign *) * (count_tokens(*tokens) + 1));
	if (result == NULL)
		return (free_tokens(*tokens), NULL);
	cur = *tokens;
	i = 0;
	while (cur != NULL && cur->type == STRING_TOKEN
		&& !is_quote(cur->content.string[0]) && ft_strchr(cur->content.string,
			'=') != NULL)
	{
		result[i++] = to_assign(cur->content.string);
		if (cur->next != NULL)
		{
			cur = cur->next;
			free_token(cur->previous);
		}
		else
			free_token(cur);
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

static int	count_tokens(t_token *tokens)
{
	int	len;

	len = 0;
	while (tokens != NULL && tokens->type == STRING_TOKEN
		&& !is_quote(tokens->content.string[0])
		&& ft_strchr(tokens->content.string, '=') != NULL)
	{
		len++;
		tokens = tokens->next;
	}
	return (len);
}

static int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}
