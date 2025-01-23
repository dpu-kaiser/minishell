/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_redirs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 13:49:31 by dkaiser           #+#    #+#             */
/*   Updated: 2025/01/23 18:22:04 by chuhlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static void				collect_and_check_redir(t_redirection *result,
							t_token **cur, t_minidata *data, t_token **tokens);
static t_redirection	*set_redir(t_redirection *redir, int type, char *spec,
							t_env *env);
static int				set_heredoc_data(t_token *cur, t_redirection *result,
							t_env *env);

t_redirection	*collect_redirs(t_token **tokens, t_env *env,
		t_list **create_files)// tokes is possition after pipe or first token
{
	t_redirection	*result;
	t_token			*cur;
	t_minidata		data;

	cur = *tokens;
	result = malloc(sizeof(t_redirection) * 2);
	if (result == NULL)
		return (free_tokens(*tokens), NULL);
	free(set_redir(&result[0], 0, NULL, env));// no token use
	free(set_redir(&result[1], 0, NULL, env));// no token use
	data.create_files = create_files;
	data.env = env;
	while (cur != NULL)
	{
		if (cur->type == REDIR_TOKEN && cur->next->type == STRING_TOKEN)//could this be a problem with recursion?
			collect_and_check_redir(result, &cur, &data, tokens);// cur=token is just in there to free and connect dont know if its ok
			//return or better said does 
		else if (cur->type == REDIR_TOKEN)
			return (free(result), NULL);
		else
			cur = cur->next;
	}
	return (result);
}

static void	collect_and_check_redir(t_redirection *result, t_token **cur,
		t_minidata *data, t_token **tokens)
{
	char	*str;

	if ((*cur)->content.redir_type != INPUT_LIMITER)
		str = ft_strdup((*cur)->next->content.string);
	if ((*cur)->content.redir_type == INPUT_LIMITER)
	{
		if (!set_heredoc_data(*cur, result, data->env))// set here doc data with token head or first token after pipe
			return ;
	}
	else if ((*cur)->content.redir_type == INPUT_FILE)
		q4fc(data->create_files, set_redir(&result[0], INPUT_FILE,
				format_string(str, data->env, 0), data->env));//here toke list should be not messed up
	else if ((*cur)->content.redir_type == OUTPUT_OVERRIDE)
		q4fc(data->create_files, set_redir(&result[1], OUTPUT_OVERRIDE,
				format_string(str, data->env, 0), data->env));
	else if ((*cur)->content.redir_type == OUTPUT_APPEND) 
		q4fc(data->create_files, set_redir(&result[1], OUTPUT_APPEND,
				format_string(str, data->env, 0), data->env));
	i_love_the_norme(cur, tokens);// takes adress of token head or pos after pipe and the token specifer
}// i love the norm simple does free token and connect
//later more detailes

static t_redirection	*set_redir(t_redirection *redir, int type, char *spec,
		t_env *env)
{
	t_redirection	*result;

	redir->type = type;
	// if (redir->specifier != NULL)
	// 	free(redir->specifier);
	if (spec != NULL)
		redir->specifier = format_string(spec, env, ft_atoi("0"));
	else
		redir->specifier = spec;
	if (redir->type != INPUT_LIMITER)
	{
		result = malloc(sizeof(t_redirection));
		if (!result)
			return (NULL);
		result->type = type;
		result->specifier = spec;
		return (result);
	}
	return (NULL);
}

static int	set_heredoc_data(t_token *cur, t_redirection *result, t_env *env)
{
	char	*heredoc_data;

	heredoc_data = NULL;
	if (cur->content.redir_type == INPUT_LIMITER)
	{
		heredoc_data = read_heredoc(cur->next->content.string);
		if (!heredoc_data)
		{
			perror("Heredoc allocation failed");
			return (0);
		}
		set_redir(&result[0], INPUT_LIMITER, heredoc_data, env);
	}
	set_redir(&result[0], INPUT_LIMITER, heredoc_data, env);
	return (1);
}
