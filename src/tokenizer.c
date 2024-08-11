/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 20:55:50 by chuhlig           #+#    #+#             */
/*   Updated: 2024/08/11 11:40:35 by dkaiser          ###   ########.fr       */
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

void	handle_special_chars(char *s, int *i, int *start, t_token **token_list)
{
	conditional_print(s, *start, *i - 1, token_list);
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
	if (s[*i + 1] == '<' || s[*i + 1] == '>')
		(*i)++;
	*start = *i + 1;
}

void	tokenizer(char *s, t_token **token_list)
{
	char	quote_check;
	int		pos;
	int		i;
	int		f;

	pos = 0;
	i = -1;
	f = 0;
	while (s[++i])
	{
		if (!f && ft_strchr("|<>\n", s[i]))
			handle_special_chars(s, &i, &pos, token_list);
		else if (f && s[i] == quote_check)
			f = 0;
		else if (!f && ft_strchr("\'\"", s[i]))
		{
			f = 1;
			quote_check = s[i];
		}
		if ((!f && (s[i] == ' ' || s[i] == '\t')) || i == ft_strlen(s) - 1)
		{
			conditional_print(s, pos, i, token_list);
			pos = i + 1;
		}
	}
	while ((*token_list)->previous)
		*token_list = (*token_list)->previous;
}
