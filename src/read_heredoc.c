/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:22:09 by dkaiser           #+#    #+#             */
/*   Updated: 2025/01/15 19:08:07 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <stdio.h>
#include <sys/errno.h>

static char	*concat_str(char *temp, char *line);
static char	*get_result(char *temp, char *result, char *line);
static void	*print_error_and_free(char *result);

char	*read_heredoc(char *delimiter)
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
			return (print_error_and_free(result));
		result = get_result(temp, result, line);
		total_length += line_length;
	}
	return (result);
}

static char	*concat_str(char *temp, char *line)
{
	ft_strcat(temp, line);
	ft_strcat(temp, "\n");
	free(line);
	return (temp);
}

static char	*get_result(char *temp, char *result, char *line)
{
	if (result)
	{
		ft_strcpy(temp, result);
		free(result);
	}
	else
		temp[0] = '\0';
	return (concat_str(temp, line));
}

static void	*print_error_and_free(char *result)
{
	errno = ENOMEM;
	perror("heredoc");
	free(result);
	return (NULL);
}
