/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_part_three.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 18:29:24 by chuhlig           #+#    #+#             */
/*   Updated: 2025/01/20 17:08:17 by chuhlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	exit_shell(t_env **env, int exit_status)
{
	free_envlst(env);
	exit(exit_status);
}

int	builtin_exit(char **av, t_env **env)
{
	int	exit_status;

	if (av[1] && !av[2])
		exit_status = ft_atoi(av[1]);
	else if (av[2])
		exit_status = 1;
	else
		exit_status = 0;
	exit_shell(env, exit_status);
	return (exit_status);
}

void	set_return_code(int return_code, t_env **env)
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

int	check_flag(int f)
{
	if (f)
		return (1);
	return (0);
}
