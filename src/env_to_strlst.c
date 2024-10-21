/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_strlst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:52:08 by dkaiser           #+#    #+#             */
/*   Updated: 2024/10/21 15:07:33 by dkaiser          ###   ########.fr       */
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
