/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 20:55:50 by chuhlig           #+#    #+#             */
/*   Updated: 2024/08/09 11:43:51 by chuhlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

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

void	conditional_print(char *string, int start_of_string, int i, t_token **token_list)
{
	char	*line;
	int		len;

	len = i - start_of_string;
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

void	handle_special_chars(char *s, int *i, int *start, t_token **token_list)
{
	conditional_print(s, *start, *i, token_list);  // Pass correct boundaries
	if (s[*i] == '<' && s[*i + 1] == '<')
		*token_list = new_redir_token(INPUT_LIMITER, *token_list, NULL);
	else if (s[*i] == '>' && s[*i + 1] == '>')
		*token_list = new_redir_token(OUTPUT_APPEND, *token_list, NULL);
	else if (s[*i] == '<')
		*token_list = new_redir_token(INPUT_FILE, *token_list, NULL);
	else if (s[*i] == '>')
		*token_list = new_redir_token(OUTPUT_OVERRIDE, *token_list, NULL);
	else if (s[*i] == '|')
		*token_list = new_token(PIPE_TOKEN, *token_list, NULL);
	else if (s[*i] == '\n')
		*token_list = new_token(NEWLINE_TOKEN, *token_list, NULL);
	print_token(*token_list);
	if (s[*i] == '<' || s[*i] == '>')
		(*i)++;
	*start = *i + 1;
}

void	tokenizer(char *s, t_token **token_list)
{
	char	quote_check;
	int		pos;
	int		i;
	int		f;

	f = 0;
	i = -1;
	pos = 0;
	while (s[++i])
	{
		if (!f && ft_strchr("|<>\\n", s[i]))
			handle_special_chars(s, &i, &pos, token_list);
		else if (f && s[i] == quote_check)
			f = 0;
		else if (!f && ft_strchr("\'\"", s[i]))
		{
			f = 1;
			quote_check = s[i];
		}
		if ((!f && (s[i] == ' ' || s[i] == '\t')) || s[i + 1] == '\0')
		{
			conditional_print(s, pos, i, token_list);
			pos = i + 1;
		}
	}
}

// Minishell $ echo "Hello World"|grep 'Hello|cat -e
// STRING_TOKEN: echo 
// STRING_TOKEN: "Hello World"
// PIPE_TOKEN
// STRING_TOKEN: grep 
// STRING_TOKEN: 'Hello|cat -e
// Minishell $ 

// Minishell $ Minishell $ echo "Hello World"|grep 'Hello|cat -e
// STRING_TOKEN: echo 
// STRING_TOKEN: "Hello World"
// PIPE_TOKEN
// STRING_TOKEN: grep 
// STRING_TOKEN: 'Hello|cat -e
// Minishell $ 
// STRING_TOKEN: Mi
// STRING_TOKEN: Mi
// STRING_TOKEN: ishell 
// STRING_TOKEN: $ 
// STRING_TOKEN: echo 
// STRING_TOKEN: "Hello World"
// PIPE_TOKEN
// STRING_TOKEN: grep 
// STRING_TOKEN: 'Hello|cat -e
// STRING_TOKEN: echo 
// STRING_TOKEN: "Hello World"
// PIPE_TOKEN
// STRING_TOKEN: grep 
// STRING_TOKEN: 'Hello
// PIPE_TOKEN
// STRING_TOKEN: cat 
// STRING_TOKEN: -e
// Mi
// STRING_TOKEN: -e
// Mi
// STRING_TOKEN: ishell 
// STRING_TOKEN: $ 
// Minishell $ echo "Hello World"|grep 'Hello|cat -e
// STRING_TOKEN: echo 
// STRING_TOKEN: "Hello World"
// PIPE_TOKEN
// STRING_TOKEN: grep 
// STRING_TOKEN: 'Hello|cat -e
// Minishell $ echo "Hello World"|grep 'Hello|cat -e
// STRING_TOKEN: echo 
// STRING_TOKEN: "Hello World"
// PIPE_TOKEN
// STRING_TOKEN: grep 
// STRING_TOKEN: 'Hello|cat -e
// Minishell $ echo "Hello World"|grep 'Hello|cat -e
// STRING_TOKEN: echo 
// STRING_TOKEN: "Hello World"
// PIPE_TOKEN
// STRING_TOKEN: grep 
// STRING_TOKEN: 'Hello|cat -e
// Minishell $ echo "Hello World"|grep 'Hello'|cat -e
// STRING_TOKEN: echo 
// STRING_TOKEN: "Hello World"
// PIPE_TOKEN
// STRING_TOKEN: grep 
// STRING_TOKEN: 'Hello'
// PIPE_TOKEN
// STRING_TOKEN: cat 
// STRING_TOKEN: -e