/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:07:04 by dkaiser           #+#    #+#             */
/*   Updated: 2025/01/23 17:42:33 by chuhlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "token.h"

t_token *shallow_copy_token(t_token *token)
{
	if (token == NULL)
		return (NULL);

	if (token->type == STRING_TOKEN)
		return (new_str_token(token->content.string, NULL, NULL));
	else if (token->type == REDIR_TOKEN)
		return (new_redir_token(token->content.redir_type, NULL, NULL));
	else
		return (new_redir_token(token->type, NULL, NULL));
}

t_token *shallow_copy_tokens(t_token *tokens)
{
	t_token *result;
	t_token *cur;

	result = shallow_copy_token(tokens);
	if (!result)
		return (NULL);
	cur = result;
	while (tokens->next != NULL)
	{
		tokens = tokens->next;
		cur->next = shallow_copy_tokens(tokens);
		cur = cur->next;
	}
	return (result);
}

void	free_repl(char *input, t_node *ast)
{
	free(input);
	if(ast)
		free_node(ast);
}

void	repl(const char *prompt, t_env **env, int *promptflag)
{
	char	*input;
	t_token	*token_list;
	t_node	*ast;
	t_token *tokens_copy;

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
		tokens_copy = shallow_copy_tokens(token_list);
		free_tokens(tokens_copy);
		// print_token_list(token_list);
		ast = parse(token_list, env);
		if (ast)
			set_return_code(eval(ast, env), env);
		free_repl(input, ast);
		print_token_list(tokens_copy);
	}
}
