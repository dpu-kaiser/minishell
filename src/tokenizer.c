/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 20:55:50 by chuhlig           #+#    #+#             */
/*   Updated: 2024/06/28 21:58:38 by chuhlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

char	*ft_strncpy(char *dst, char *src, size_t n)
{
	char *start;

	start = dst;
	while (n-- > 0 && *src)
		*dst++ = *src++;
	if (n > 0)
		ft_memset(dst, '\0', n);
	return (start);
}

void	print_token(t_token *token)
{
	if (token->type == STRING_TOKEN)
	{
		printf("STRING_TOKEN: %s\n", token->content.string);
	}
	else if (token->type == REDIR_TOKEN)
	{
		printf("REDIR_TOKEN: %d\n", token->content.redir_type);
	}
	else if (token->type == PIPE_TOKEN)
	{
		printf("PIPE_TOKEN\n");
	}
}



void	conditional_print(char *string, int start_of_string, int i, int offset, t_token **token_list)
{
	char	*trimmed_line;
	char	*line;
	int		len;

	len = i + offset - start_of_string;
	if (len > 0)
	{
		line = (char *)malloc(len + 1);
		if (!line)
		{
			exit(EXIT_FAILURE);
		}
		ft_strncpy(line, string + start_of_string, len);
		line[len] = '\0';
		trimmed_line = line;
		while (*trimmed_line == ' ' || *trimmed_line == '\t')
		{
			trimmed_line++;
		}
		if (*trimmed_line != '\0')
		{
			*token_list = new_str_token(trimmed_line, *token_list, NULL);
			print_token(*token_list);
		}
		free(line);
	}
}

void	tokenizer(char *s, t_token **token_list)
{
	char	*quotes;
	char	quote_check;
	char	c;
	int		start_of_string;
	int		ignore_space;
	int		flag;
	int		i;
	int		skip;

	quotes = "\"\'";
	quote_check = '\0';
	start_of_string = 0;
	ignore_space = 0;
	flag = 0;
	i = 0;
	skip = 0;
	while (s[i])
	{
		c = s[i];
		if (skip)
		{
			skip = 0;
			i++;
			continue ;
		}
		if (!ignore_space && (c == '|' || c == ';' || c == '<' || c == '>'))
		{
			conditional_print(s, start_of_string, i, 0, token_list);
			if ((c == '<' || c == '>') && s[i + 1] == c)
			{
				if (c == '<')
				{
					*token_list = new_redir_token(INPUT_FILE,
							*token_list, NULL);
					print_token(*token_list);
				}
				else
				{
					*token_list = new_redir_token(OUTPUT_APPEND,
							*token_list, NULL);
					print_token(*token_list);
				}
				i++;
			}
			else
			{
				if (c == '<')
				{
					*token_list = new_redir_token(INPUT_FILE,
							*token_list, NULL);
				}
				else
				{
					*token_list = new_redir_token(OUTPUT_OVERRIDE,
							*token_list, NULL);
				}
				print_token(*token_list);
			}
			start_of_string = i + 1;
		}
		else if (ignore_space && c == quote_check)
		{
			quote_check = '\0';
			ignore_space = 0;
		}
		else if (!ignore_space && ft_strchr(quotes, c))
		{
			quote_check = c;
			ignore_space = 1;
		}
		else if ((!ignore_space && (s[i] != ' ' || s[i] != '\t')) || s[i + 1] == '\0')
		{
			if (s[i + 1])
				conditional_print(s, start_of_string, i, 1, token_list);
			else
				conditional_print(s, start_of_string, i, 0, token_list);
			start_of_string = i + 1;
		}
		i++;
	}
}