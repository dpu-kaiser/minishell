/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   praise_the_norme.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:35:41 by dkaiser           #+#    #+#             */
/*   Updated: 2025/01/25 17:13:20 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	i_love_the_norme(t_token **cur, t_token **tokens)
{
	t_token	*next_token;

	next_token = (*cur)->next;
	if (next_token)
	{
		if ((*cur)->type != REDIR_TOKEN || ((*cur)->previous))
			free_token_and_connect(*cur);
		*cur = NULL;
		if (next_token->previous == NULL)
			*tokens = next_token->next;
		*cur = next_token->next;
		free_token_and_connect(next_token);
	}
	else
		*cur = NULL;
}

void	*free_redirs(t_redirection *redirs, t_list **create_files)
{
	ft_lstclear(create_files, free_file);
	if (redirs[0].type != 0)
		free(redirs[0].specifier);
	if (redirs[1].type != 0)
		free(redirs[1].specifier);
	free(redirs);
	return (NULL);
}

void	free_file(void *arg)
{
	t_redirection	*file;

	file = (t_redirection *)arg;
	free(file->specifier);
	free(file);
}
