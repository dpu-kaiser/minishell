/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:07:04 by dkaiser           #+#    #+#             */
/*   Updated: 2024/07/15 19:53:52 by chuhlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "token.h"

void	repl(const char *prompt)
{
	char	*input;
	t_token	*token_list;
	t_token *current;
	t_token *next;

	while (1)
	{
		input = readline(prompt);
		if (input == NULL)
			return ;
		add_history(input);
		token_list = NULL;
		tokenizer(input, &token_list);
		current = token_list;
		while (current != NULL)
		{
			next = current->next;
			free_token(current);
			current = next;
		}
		free(input);
	}
}
