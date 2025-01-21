/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:07:04 by dkaiser           #+#    #+#             */
/*   Updated: 2025/01/21 13:39:43 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "token.h"

void	free_ast(void *arg)
{
	t_node	*ast;

	if (arg)
	{
		ast = (t_node *)arg;
		free_node(ast);
	}
}

void	free_repl(char *input, t_list **lines)
{
	free(input);
	ft_lstclear(lines, free_ast);
}

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
		free_repl(input, &lines);
	}
}
