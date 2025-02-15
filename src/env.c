/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:31:07 by chuhlig           #+#    #+#             */
/*   Updated: 2025/01/20 19:12:43 by chuhlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "minishell.h"
#include <stdlib.h>

void	getenvlst(t_env **env, char **en)
{
	char	*tmp;
	int		i;
	t_env	*current;

	i = 0;
	while (en[i] != NULL)
	{
		tmp = ft_strchr(en[i], '=');
		*tmp = '\0';
		current = *env;
		current = malloc(sizeof(t_env));
		current->name = ft_strdup(en[i]);
		current->value = ft_strdup(tmp + 1);
		current->next = *env;
		*env = current;
		i++;
	}
}

void	free_envlst(t_env **env)
{
	t_env	*cur;
	t_env	*new;

	cur = *env;
	while (cur)
	{
		new = cur->next;
		free(cur->name);
		free(cur->value);
		free(cur);
		cur = new;
	}
}

char	*env_get(t_env *env, char *name)
{
	while (env != NULL)
	{
		if (!ft_strncmp(env->name, name, ft_strlen(env->name)))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

t_env	*env_new(char *name)
{
	t_env	*result;

	result = malloc(sizeof(t_env));
	if (!result)
		return (NULL);
	result->name = name;
	return (result);
}

void	free_env_node(t_env *node)
{
	free(node->name);
	free(node->value);
	free(node);
}
