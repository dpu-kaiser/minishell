/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_assigns.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 13:54:36 by dkaiser           #+#    #+#             */
/*   Updated: 2024/08/02 13:55:13 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_assign	*to_assign(char *str);

t_assign	**collect_assigns(t_token **tokens)
{
	t_token		*cur;
	t_assign	**result;
	int			i;

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
		if (cur->next != NULL)
		{
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
