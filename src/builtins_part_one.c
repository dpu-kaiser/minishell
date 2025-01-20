/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_part_one.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:01:16 by chuhlig           #+#    #+#             */
/*   Updated: 2025/01/18 18:33:33 by chuhlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <stdio.h>

int	unset(char **av, t_env **env)
{
	t_env	*current;
	t_env	*prev;
	int		i;

	i = 0;
	while (av[++i])
	{
		current = *env;
		prev = NULL;
		while (current)
		{
			if (ft_strcmp(current->name, av[i]) == 0)
			{
				if (prev)
					prev->next = current->next;
				else
					*env = current->next;
				free_env_node(current);
				break ;
			}
			prev = current;
			current = current->next;
		}
	}
	return (0);
}

t_env	*check_existing(t_env *env, char *av)
{
	while (env)
	{
		if (ft_strcmp("$", av) == 0)
			return (NULL);
		if (ft_strcmp(env->name, av) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	export_export(char *av, t_env **env)
{
	char	*tmp;
	t_env	*current;

	current = NULL;
	tmp = ft_strchr(av, '=');
	*tmp = '\0';
	current = check_existing(*env, av);
	if (current)
		free(current->value);
	else
	{
		current = env_new(ft_strdup(av));
		current->next = *env;
		*env = current;
	}
	current->value = ft_strdup(tmp + 1);
}

int	is_valid_identifier(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	export(char **av, t_env **env)
{
	char	*equal_sign;
	int		i;

	i = 0;
	while (av[++i])
	{
		equal_sign = ft_strchr(av[i], '=');
		if (equal_sign)
			*equal_sign = '\0';
		if (!is_valid_identifier(av[i]))
		{
			write(1, "Minishell $ export: not a valid identifier\n", 43);
			if (equal_sign)
				*equal_sign = '=';
			continue ;
		}
		if (equal_sign)
		{
			*equal_sign = '=';
			export_export(av[i], env);
		}
	}
	return (0);
}
