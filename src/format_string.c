/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:30:11 by chuhlig           #+#    #+#             */
/*   Updated: 2025/01/14 18:06:17 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include "minishell.h"

static void	append_slice(char **dst, char *src, int start, int end);
static void	append_var(char **dst, char *src, int *pos, t_env *env);

char	*format_string(char *str, t_env *env)
{
	char	*result;
	int		pos;
	int		start;
	int		is_literal;

	pos = 0;
	start = 0;
	is_literal = 0;
	result = NULL;
	if (str == NULL)
		return (NULL);
	while (str[pos] != '\0')
	{
		if (str[pos] == '\'')
		{
			append_slice(&result, str, start, pos);
			start = pos + 1;
			is_literal = !is_literal;
		}
		if (str[pos] == '"' && !is_literal)
		{
			append_slice(&result, str, start, pos);
			start = pos + 1;
		}
		if (str[pos] == '$' && !is_literal)
		{
			append_slice(&result, str, start, pos);
			append_var(&result, str, &pos, env);
			start = pos;
			continue ;
		}
		pos++;
	}
	append_slice(&result, str, start, pos);
	return (result);
}

static void	append_slice(char **dst, char *src, int start, int end)
{
	char	*result;
	int		len;
	int		i;

	if (*dst != NULL)
		len = ft_strlen(*dst);
	else
	{
		len = 0;
	}
	result = malloc(len + (end - start) + 1);
	if (!result)
		return ;
	ft_strncpy(result, *dst, len);
	i = 0;
	while (start + i < end)
	{
		result[len + i] = src[start + i];
		i++;
	}
	result[len + i] = '\0';
	if (*dst != NULL)
		free(*dst);
	*dst = result;
}

static void	append_var(char **dst, char *src, int *pos, t_env *env)
{
	int		i;
	char	*var;
	char	*value;
	char	*result;

	i = 0;
	*pos += 1;
	while (src[*pos + i] != '\0' && src[*pos + i] != '\'' && src[*pos
		+ i] != '"' && src[*pos + i] != '$')
	{
		i++;
	}
	var = malloc(i + 1);
	if (var == NULL)
		return ;
	var[i] = '\0';
	i--;
	while (i >= 0)
	{
		var[i] = src[*pos + i];
		i--;
	}
	value = env_get(env, var);
	if (value != NULL)
	{
		result = ft_strjoin(*dst, value);
		free(*dst);
		*dst = result;
	}
	*pos += ft_strlen(var);
}
