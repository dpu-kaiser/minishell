/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_part_two.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 20:52:16 by chuhlig           #+#    #+#             */
/*   Updated: 2025/01/20 19:12:33 by chuhlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	update_oldpwd(t_env **env)
{
	t_env	*current;
	t_env	*prev;
	char	cwd[1028];
	char	*tmp;

	prev = NULL;
	current = *env;
	while (current)
	{
		if (ft_strncmp(current->name, "OLDPWD", 6) == 0)
			break ;
		prev = current;
		current = current->next;
	}
	getcwd(cwd, sizeof(cwd));
	tmp = ft_strdup(cwd);
	free(current->value);
	current->value = tmp;
}

void	update_pwd(t_env **env)
{
	t_env	*current;
	t_env	*prev;
	char	cwd[1028];
	char	*tmp;

	prev = NULL;
	current = *env;
	while (current)
	{
		if (ft_strncmp(current->name, "PWD", 3) == 0)
			break ;
		prev = current;
		current = current->next;
	}
	getcwd(cwd, sizeof(cwd));
	tmp = ft_strdup(cwd);
	free(current->value);
	current->value = tmp;
}

int	cd(t_env **env, char **av)
{
	t_env	*current;

	current = *env;
	if (av[1] == NULL)
	{
		update_oldpwd(env);
		while (current)
		{
			if (ft_strncmp(current->name, "HOME", 4) == 0)
				break ;
			current = current->next;
		}
		if (chdir(current->value) == -1)
			return (1);
		update_pwd(env);
	}
	else
	{
		update_oldpwd(env);
		if (chdir(av[1]) == -1)
			return (1);
		update_pwd(env);
	}
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
		if (ft_strchr(env->name, '?'))
		{
			env = env->next;
			continue ;
		}
		printf("%s", env->name);
		printf("=%s\n", env->value);
		env = env->next;
	}
	return (0);
}
