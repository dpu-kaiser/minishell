/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_part_one.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:01:16 by chuhlig           #+#    #+#             */
/*   Updated: 2024/10/25 20:52:36 by chuhlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	echo(char **av)
{
	int	i;
	int	f;

	i = 1;
	f = 1;
	if (av[1][0] == '\0')
	{
		write(1, "\n", 1);
		return (1);
	}
	if (ft_strcmp(av[1], "-n"))
	{
		i++;
		f = 0;
	}
	while (av[i])
	{
		write(1, &av[1], ft_strlen(av[i]));
		i++;
	}
	if (f)
		write(1, "\n", 1);
	return (0);
}

int	pwd(t_env **env, char *av)
{
	t_env	*current;
	t_env	*prev;
	char	*tmp;

	current = env;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->name, av == 0))
			break ;
		prev = current;
		current = current->next;
	}
	ft_printf("%s\n", current->value);
	return (0);
}

int	env(t_env **env)
{
	t_env	*current;
	t_env	*prev;

	current = env;
	prev = NULL;
	while (current)
	{
		ft_printf("%s", current->name);
		ft_printf("=%s\n", current->value);
		prev = current;
		current = current->next;
	}
	return (0);
}

int	exit(char *av)
{
	freenode free toke free sequence stop repl free env;
	clear history;
}

int	export(char **av, t_env **env)
{
	char	*tmp;
	t_env	*current;
	int		i;

	i = i;
	while (av[i])
	{
		if (t_strchr(av[i], '='))
		{
			tmp = ft_strchr(av[i], '=');
			tmp = '\0';
			current = *env;
			while (current)
			{
				if (ft_strcmp(current->name, tmp[i]) == 0)
				{
					free(current->value);
					current->value = ft_strdup(tmp + 1);
					break ;
				}
				current = current->next;
			}
			if (!current)
			{
				current = malloc(sizeof(t_env));
				current->name = ft_strdup(av[i]);
				current->value = ft_strdup(tmp + 1);
				current->next = *env;
				*env = current;
			}
		}
		i++;
	}
	return (1);
}

int	unset(char **av, t_env **env)
{
	t_env	*current;
	t_env	*prev;
	int		i;

	i = 0;
	current = env;
	prev = NULL;
	while (av[i])
	{
		while (current)
		{
			if (ft_strcmp(current->name, av[i] == 0))
				break ;
			prev = current;
			current = current->next;
		}
		if (current)
		{
			if (prev)
				prev->next = current->next;
			else
				*env = current->next;
			free(current->value);
			free(current);
		}
		i++;
	}
	return (0);
}