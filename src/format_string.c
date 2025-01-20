/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:30:11 by chuhlig           #+#    #+#             */
/*   Updated: 2025/01/19 20:24:05 by chuhlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include "minishell.h"

void	append_var_exit_code(char **dst, t_env *env)
{
	char	*exit_code;
	char	*result;

	exit_code = env_get(env, "?");
	if (exit_code)
	{
		result = ft_strjoin(*dst, exit_code);
		free(*dst);
		*dst = result;
	}
}

static void	append_slice(char **dst, char *src, int start, int end)
{
	char	*result;
	int		len;
	int		i;

	if (*dst != NULL)
		len = ft_strlen(*dst);
	else
		len = 0;
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
	while (ft_isalnum(src[*pos + i]) || src[*pos + i] == '_')
		i++;
	if (i == 0)
		return ;
	var = ft_substr(src, *pos, i);
	value = env_get(env, var);
	if (value)
	{
		result = ft_strjoin(*dst, value);
		free(*dst);
		*dst = result;
	}
	*pos += i;
	free(var);
}

static void	handle_dollar_sign(char **result, char *str, int *pos, t_env *env)
{
	if (str[*pos + 1] == '?')
	{
		append_var_exit_code(result, env);
		*pos += 2;
	}
	else if (ft_isalnum(str[*pos + 1]) || str[*pos + 1] == '_')
		append_var(result, str, pos, env);
	else
	{
		append_slice(result, str, *pos, *pos + 1);
		(*pos)++;
	}
}

char	*format_string(char *str, t_env *env, int is_literal)
{
	char	*result;
	int		pos;
	int		start;

	pos = 0;
	start = 0;
	result = NULL;
	if (!str)
		return (NULL);
	while (str[pos])
	{
		if (str[pos] == '\'' || (str[pos] == '\"' && !is_literal)
			|| (str[pos] == '$' && !is_literal))
		{
			append_slice(&result, str, start, pos);
			if (str[pos] == '$')
				handle_dollar_sign(&result, str, &pos, env);
			else
				is_literal ^= (str[pos++] == '\'');
			start = pos;
			continue ;
		}
		pos++;
	}
	return (append_slice(&result, str, start, pos), result);
}
