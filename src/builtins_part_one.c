/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_part_one.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:01:16 by chuhlig           #+#    #+#             */
/*   Updated: 2025/01/10 14:36:55 by chuhlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	echo(char **av)
{
	int	i;
	int	f;

	i = 1;
	f = 1;
	if (av[1] == NULL || av[1][0] == '\0')
	{
		write(1, "\n", 1);
		return (1);
	}
	if (ft_strncmp(av[1], "-n", 3) == 0)
	{
		i++;
		f = 0;
	}
	while (av[i])
	{
		write(1, av[i], ft_strlen(av[i]));
		i++;
		if (av[i])
			write(1, " ", 1);
	}
	if (f)
		write(1, "\n", 1);
	return (0);
}

int	pwd(t_env *env)
{
	while (env)
	{
		if (ft_strncmp(env->name, "PWD", 4) == 0)
		{
			ft_printf("%s\n", env->value);
			break ;
		}
		env = env->next;
	}
	return (0);
}

int	ft_env(t_env *env)
{
	while (env != NULL)
	{
		printf("%s", env->name);
		printf("=%s\n", env->value);
		env = env->next;
	}
	return (0);
}

// int	exit(char *av)
// {
// 	freenode free toke free sequence stop repl free env;
// 	clear history;
// }
////

void	free_env_node(t_env *node)
{
	free(node->name);
	free(node->value);
	free(node);
}

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

t_env	*env_new(char *name)
{
	t_env	*result;

	result = malloc(sizeof(t_env));
	if (!result)
		return (NULL);
	result->name = name;
	return (result);
}

t_env	*check_existing(t_env *env, char *av)
{
	while (env)
	{
		if (ft_strcmp(env->name, av) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

int	export(char **av, t_env **env)
{
	char	*tmp;
	t_env	*current;
	int		i;

	current = NULL;
	i = 0;
	while (av[++i])
	{
		if ((ft_strchr(av[i], '=')))
		{
			tmp = ft_strchr(av[i], '=');
			*tmp = '\0';
			current = check_existing(*env, av[i]);
			if (current)
				free(current->value);
			else
			{
				current = env_new(ft_strdup(av[i]));
				current->next = *env;
				*env = current;
			}
			current->value = ft_strdup(tmp + 1);
		}
	}
	return (0);
}