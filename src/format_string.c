/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:46:10 by dkaiser           #+#    #+#             */
/*   Updated: 2024/10/25 16:37:15 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include "minishell.h"

static void	append_slice(char **dst, char *src, int start, int end);

enum		e_format_mode
{
	LITERAL = 1,
	VARIABLE = 2,
};

char	*format_string(char *str, t_env *env)
{
	char	*result;
	int		pos;
	int		start;
	int		mode;

	*env = *env;
	pos = 0;
	start = 0;
	mode = 0;
	result = NULL;
	while (str[pos] != '\0')
	{
		if (str[pos] == '\'')
		{
            append_slice(&result, str, start, pos);
			start = pos + 1;
			mode ^= LITERAL;
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
	ft_strncpy(result, src, len);
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
