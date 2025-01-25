/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:07:04 by dkaiser           #+#    #+#             */
/*   Updated: 2025/01/25 15:39:36 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "token.h"

static void	free_repl(char *input, t_node *ast)
{
	free(input);
	if (ast)
		free_node(ast);
}

void	repl(const char *prompt, t_env **env)
{
	char	*input;
	t_token	*token_list;
	t_node	*ast;

	while (1)
	{
		input = readline(prompt);
		if (input == NULL)
		{
			printf("exit\n");
			break ;
		}
		if (input[0] == '\0')
		{
			free(input);
			continue ;
		}
		add_history(input);
		token_list = NULL;
		tokenizer(input, &token_list, '\0');
		ast = parse(token_list, env);
		if (ast)
			set_return_code(eval(ast, env), env);
		free_repl(input, ast);
	}
}
