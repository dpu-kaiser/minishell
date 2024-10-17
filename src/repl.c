/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:07:04 by dkaiser           #+#    #+#             */
/*   Updated: 2024/10/17 15:25:48 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "token.h"

void	repl(const char *prompt, t_env *env)
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
		lines = parse(token_list);
		if (lines)
		{
			print_ast(lines->content);
			eval(lines->content, env);
		}
		free(input);
	}
}
