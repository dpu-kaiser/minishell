/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 20:55:50 by chuhlig           #+#    #+#             */
/*   Updated: 2024/08/08 18:50:53 by chuhlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

void	print_token(t_token *token)
{
	if (DEBUG)
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
}


void	conditional_print(char *string, int start_of_string, int i,
	t_token **token_list)
{
	char	*line;
	int		len;

	len = i - start_of_string + 1;
	if (len > 0)
	{
		line = (char *)malloc(len + 1);
		if (!line)
		{
			exit(EXIT_FAILURE);
		}
		ft_strncpy(line, string + start_of_string, len);
		line[len] = '\0';
		while (*line == ' ' || *line == '\t')
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
		return ;
	while (s[i])
	{
		if (!ignore_space && (s[i] == '|' || s[i] == '\n' || s[i] == '<' || s[i] == '>'))
		{
			conditional_print(s, start_of_string, i - 1, token_list);
			if ((s[i] == '<' || s[i] == '>') && s[i + 1] == s[i])
			{
				if (s[i] == '<')
					*token_list = new_redir_token(INPUT_LIMITER, *token_list, NULL);
				else
					*token_list = new_redir_token(OUTPUT_APPEND, *token_list, NULL);
				i++;
			}
			else
			{
				if (s[i] == '<')
					*token_list = new_redir_token(INPUT_FILE, *token_list, NULL);
				else if (s[i] == '|')
					*token_list = new_token(PIPE_TOKEN, *token_list, NULL);
				else if (s[i] == '\n')
					*token_list = new_token(NEWLINE_TOKEN, *token_list, NULL);
				else
					*token_list = new_redir_token(OUTPUT_OVERRIDE, *token_list, NULL);
			}
			print_token(*token_list);
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
		else if ((!ignore_space && (s[i] == ' ' || s[i] == '\t')) || i == ft_strlen(s) - 1)
		{
			conditional_print(s, start_of_string, i, token_list);
			start_of_string = i + 1;
		}
		i++;
	}
}


// Minishell $ |abc|cba
// PIPE_TOKEN
// STRING_TOKEN: abc
// PIPE_TOKEN
// STRING_TOKEN: cba
// Minishell $   ||abc  a||cba
// PIPE_TOKEN
// PIPE_TOKEN
// STRING_TOKEN: abc 
// STRING_TOKEN: a
// PIPE_TOKEN
// PIPE_TOKEN
// STRING_TOKEN: cba
// Minishell $ 