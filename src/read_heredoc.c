/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:22:09 by dkaiser           #+#    #+#             */
/*   Updated: 2025/01/15 18:22:52 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
