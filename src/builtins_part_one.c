/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_part_one.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:01:16 by chuhlig           #+#    #+#             */
/*   Updated: 2025/01/14 19:51:59 by chuhlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <stdio.h>

int	echo(char **av)
{
	int	i;
	int	f;

	i = 1;
	f = 1;
	if (av[1] == NULL || av[1][0] == '\0')
	{
		write(1, "\n", 1);
		return (0);
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

void	exit_shell(t_env **env, int exit_status)
{
	free_envlst(env);
	exit(exit_status);
}

int	builtin_exit(char **args, t_env **env)
{
	int	exit_status;

	if (args[1])
		exit_status = ft_atoi(args[1]);
	else
		exit_status = 0;
	exit_shell(env, exit_status);
	return (exit_status);
}

int	unset(char **av, t_env **env)
{
	t_env	*current;
	t_env	*prev;
	int		i;

	i = 0;
	while (av[++i])
	{
		if (ft_strchr(av[i], '?'))
			return (1);
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
			if (ft_strchr(av[i], '?'))
				return (1);
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
		else
			return (1);
	}
	return (0);
}

void set_return_code(int return_code, t_env **env)
{
	t_env	*cur;

	cur = check_existing(*env, "?");
	if (cur)
		free(cur->value);
	else
	{
		cur = env_new(ft_strdup("?"));
		cur->next = *env;
		*env = cur;
	}
	cur->value = ft_itoa(return_code);
}
