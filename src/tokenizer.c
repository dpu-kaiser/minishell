/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 20:55:50 by chuhlig           #+#    #+#             */
/*   Updated: 2024/07/22 18:41:53 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

char	*ft_strncpy(char *s1, char *s2, int n)
{
	int	i;

	i = -1;
	while (++i < n && s2[i])
		s1[i] = s2[i];
	s1[i] = '\0';
	return (s1);
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
	else if (token->type == NEWLINE_TOKEN)
	{
		printf("NEWLINE_TOKEN\n");
	}
}

void	conditional_print(char *string, int start_of_string, int i, int offset,
		t_token **token_list)
{
	char	*line;
	int		len;

	len = i + offset - start_of_string + 1;
	if (len > 0)
	{
		line = (char *)malloc(len);
		if (!line)
		{
			exit(EXIT_FAILURE);
		}
		ft_strncpy(line, string + start_of_string, len);
		line[len] = '\0';
		while (*line == ' ' || *line == '\t' /* || *line == '\0' */)
			line++;
		if (*line != '\0')
		{
			*token_list = new_str_token(line, *token_list, NULL);
			print_token(*token_list);
		}
	}
}

void	tokenizer(char *s, t_token **token_list)
{
	char	*quotes;
	char	quote_check;
	int		start_of_string;
	int		ignore_space;
	int		i;

	quotes = "\"\'";
	quote_check = '\0';
	start_of_string = 0;
	ignore_space = 0;
	i = 0;
	if (!s || !*s)
	{
		*token_list = NULL;
		return;
	}
	while (s && s[i])
	{
		if (!ignore_space && (s[i] == '|' || s[i] == '\n' || s[i] == '<'
				|| s[i] == '>'))
		{
			/* conditional_print(s, start_of_string, i, 0, token_list); */
			if ((s[i] == '<' || s[i] == '>') && s[i + 1] == s[i])
			{
				if (s[i] == '<')
					*token_list = new_redir_token(INPUT_LIMITER, *token_list,
							NULL);
				else
					*token_list = new_redir_token(OUTPUT_APPEND, *token_list,
							NULL);
				print_token(*token_list);
				i++;
			}
			else
			{
				if (s[i] == '<')
					*token_list = new_redir_token(INPUT_FILE, *token_list,
							NULL);
				else if (s[i] == '|')
					*token_list = new_token(PIPE_TOKEN, *token_list, NULL);
				else if (s[i] == '\n')
					*token_list = new_token(NEWLINE_TOKEN, *token_list, NULL);
				else
					*token_list = new_redir_token(OUTPUT_OVERRIDE, *token_list,
							NULL);
				print_token(*token_list);
			}
			start_of_string = i + 1;
		}
		else if (ignore_space && s[i] == quote_check)
		{
			quote_check = '\0';
			ignore_space = 0;
		}
		else if (!ignore_space && ft_strchr(quotes, s[i]))
		{
			quote_check = s[i];
			ignore_space = 1;
		}
		if ((!ignore_space && (s[i] == '\0' || s[i] == ' ' || s[i] == '\t'))
			|| i == ft_strlen(s) - 1)
		{
			if (s[i + 1] == '\0')
				i++;
			conditional_print(s, start_of_string, i - 1, 0, token_list);
			start_of_string = i + 1;
		}
		i++;
	}
}
