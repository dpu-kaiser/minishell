/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_strlst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:22:28 by chuhlig           #+#    #+#             */
/*   Updated: 2025/01/14 14:41:39 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static char	*get_var_assign(t_env *cur);

char	**env_to_strlst(t_env *env)
{
	int		size;
	t_env	*cur;
	char	**result;
	int		i;

	size = 0;
	cur = env;
	while (cur != NULL)
	{
		if (ft_strchr(cur->name, '?'))
		{
			cur = cur->next;
			continue;
		}
		size++;
		cur = cur->next;
	}
	result = malloc(sizeof(char *) * (size + 1));
	if (result == NULL)
		return (NULL);
	i = 0;
	cur = env;
	while (i < size)
	{
		if (ft_strchr(cur->name, '?'))
		 cur = cur->next;
		result[i] = get_var_assign(cur);
		cur = cur->next;
		i++;
	}
	result[i] = NULL;
	return (result);
}

static char	*get_var_assign(t_env *cur)
{
	char	*left_side;
	char	*result;

	left_side = ft_strjoin(cur->name, "=");
	if (left_side == NULL)
		return (NULL);
	result = ft_strjoin(left_side, cur->value);
	free(left_side);
	return (result);
}
