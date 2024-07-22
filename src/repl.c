/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:07:04 by dkaiser           #+#    #+#             */
/*   Updated: 2024/07/22 17:13:51 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "libft.h"
#include "token.h"

void	repl(const char *prompt)
{
	char	*input;
	t_token	*token_list;
	/* t_token *current; */
	/* t_token *next; */
	t_list *seq;

	while (1)
	{
		input = readline(prompt);
		if (input == NULL)
			return ;
		add_history(input);
		token_list = NULL;
		tokenizer(input, &token_list);
		seq = parse(token_list);
		if (seq != NULL)
			print_ast(seq->content);
		/* current = token_list; */
		/* while (current != NULL) */
		/* { */
		/* 	next = current->next; */
		/* 	free_token(current); */
		/* 	current = next; */
		/* } */
		/* free(input); */
	}
}
