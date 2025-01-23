/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 15:06:25 by dkaiser           #+#    #+#             */
/*   Updated: 2025/01/23 18:04:50 by chuhlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**collect_args(t_token **tokens, t_env **env);

t_node	*parse_cmd(t_token *tokens, t_env **env)
{
	char			**args;
	t_redirection	*redirs;
	t_list			*create_files;

	create_files = NULL;
	printf("parse_cmd\n");
	print_token_list(tokens);
	redirs = collect_redirs(&tokens, *env, &create_files);// takes pos next to pipe or first token
	printf("parse_cmdafter collect redir\n");
	print_token_list(tokens);// still existing tokenlist
	if (redirs == NULL)
		return (NULL);
	args = collect_args(&tokens, env);
	printf("parse_cmdafter collect args\n");
	// print_token_list(tokens);//here it gone
	if (args == NULL)
	{
		free(redirs);
		return (NULL);
	}
	return (new_cmd_node(args, redirs, create_files));
}

// static char	**collect_args(t_token **tokens, t_env **env)
// {
// 	t_token	*cur;
// 	char	**result;
// 	int		i;
// 	t_token	*next;

// 	cur = *tokens;
// 	i = 0;
// 	while (cur != NULL && ++i)
// 		cur = cur->next;
// 	result = malloc(sizeof(char *) * (i + 1));
// 	if (result == NULL)
// 		return (free_tokens(*tokens), NULL);
// 	cur = *tokens;
// 	i = 0;
// 	while (cur != NULL && cur->type == STRING_TOKEN)
// 	{
// 		next = cur->next;
// 		if (cur->previous)
// 			free_token(cur->previous);
// 		result[i] = format_string(cur->content.string, *env, ft_atoi("0"));
// 		i++;
// 		if (cur->next == NULL)
// 			free_token(cur);
// 		cur = next;
// 	}
// 	result[i] = NULL;
// 	return (result);
// }

static char **collect_args(t_token **tokens, t_env **env) {
    t_token *cur;
    char **result;
    int i;
    t_token *next;

    cur = *tokens;
    i = 0;
    while (cur != NULL && ++i)
        cur = cur->next;
    result = malloc(sizeof(char *) * (i + 1));
    if (result == NULL)
        return (free_tokens(*tokens), NULL);
    cur = *tokens;
    i = 0;
    while (cur != NULL && cur->type == STRING_TOKEN) {
        next = cur->next;
        result[i] = format_string(cur->content.string, *env, ft_atoi("0"));
        i++;
        if (cur->previous)
            cur->previous->next = cur->next;
        if (cur->next)
            cur->next->previous = cur->previous;
        free_token(cur);
        cur = next;
    }
    result[i] = NULL;
    *tokens = cur; // Update the head of the token list
    return (result);
}// need to later the rest of the tokenlist
