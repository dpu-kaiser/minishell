/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 15:06:25 by dkaiser           #+#    #+#             */
/*   Updated: 2024/07/08 17:29:22 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "token.h"
#include <stdlib.h>
#include <string.h>

static t_redirection	**collect_redirs(t_token **tokens);
static t_assign			**collect_assigns(t_token **tokens);
static char				**collect_args(t_token **tokens);
static t_assign			*to_assign(char *str);

t_node	*parse_cmd(t_token *tokens)
{
	char			**args;
	t_assign		**assigns;
	t_redirection	redirs[2];

	redirs = collect_redirs(&tokens);
	assigns = collect_assigns(&tokens);
	args = collect_args(&tokens);
	return (new_cmd_node(args, assigns, redirs));
}

static t_redirection	**collect_redirs(t_token **tokens)
{
	return (NULL);
}

static t_assign	**collect_assigns(t_token **tokens)
{
	int			i;
	t_assign	**result;

	i = 0;
	while (ft_strchr(tokens[i]->content.string, '=') != NULL)
	{
		i++;
	}
	result = malloc(sizeof(t_assign *) * (i + 1));
	if (result == NULL)
	{
		// free everything
		return (NULL);
	}
	result[i] = NULL;
	i--;
	while (i >= 0)
	{
		result[i] = to_assign(tokens[i]->content.string);
		i--;
	}
	return (result);
}

static char	**collect_args(t_token **tokens)
{
	int		i;
	char	**result;

	i = 0;
	while (tokens[i] != NULL)
	{
		i++;
	}
	result = malloc(sizeof(char *) * (i + 1));
	if (result == NULL)
	{
		// free everything in the token
		return (NULL);
	}
	i = 0;
	while (tokens[i] != NULL)
	{
		result[i] = tokens[i]->content.string;
		free_token(tokens[i]);
		i++;
	}
	result[i] = NULL;
	return (result);
}

static t_assign	*to_assign(char *str)
{
	t_assign	*result;
	char		*split;

	result = malloc(sizeof(t_assign));
	if (result == NULL)
		return (NULL);
	split = ft_strchr(str, '=');
	if (split == NULL)
		return (NULL);
	*split = '\0';
	result->var = str;
	result->value = split + 1;
	return (result);
}
