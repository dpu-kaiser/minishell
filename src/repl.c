/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:07:04 by dkaiser           #+#    #+#             */
/*   Updated: 2025/01/11 16:01:44 by chuhlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "token.h"

t_token	*reverse_token_list(t_token *head)
{
	t_token	*prev;
	t_token	*current;
	t_token	*next;

	prev = NULL;
	current = head;
	next = NULL;
	while (current != NULL)
	{
		next = current->previous;
		current->next = prev;
		current->previous = next;
		prev = current;
		current = next;
	}
	return (prev);
}

void	repl(const char *prompt, t_env **env)
{
	char	*input;
	t_token	*token_list;
	t_list	*lines;

	while (1)
	{
		input = readline(prompt);
		if (input == NULL)
			return ;
		if (input[0] == '\0')
			continue ;
		add_history(input);
		token_list = NULL;
		tokenizer(input, &token_list, '\0');
		token_list = reverse_token_list(token_list);
		lines = parse(token_list, env);
		if (lines)
		{
			print_ast(lines->content);
			eval(lines->content, env);
		}
		free(input);
	}
}
