/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:07:04 by dkaiser           #+#    #+#             */
/*   Updated: 2025/01/14 15:39:58 by chuhlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "token.h"

void	repl(const char *prompt, t_env **env, int *promptflag)
{
	char	*input;
	t_token	*token_list;
	t_list	*lines;

	(*promptflag)++;
	while (1)
	{
		input = readline(prompt);
		if (input == NULL)
		{
			if (*promptflag > 1)
				(*promptflag)--;
			printf("exit\n");
			break ;
		}
		if (input[0] == '\0')
			continue ;
		add_history(input);
		token_list = NULL;
		tokenizer(input, &token_list, '\0');
		lines = parse(token_list, env);
		if (lines)
			set_return_code(eval(lines->content, env), env);
		free(input);
	}
}
