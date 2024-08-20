/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_part_one.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:01:16 by chuhlig           #+#    #+#             */
/*   Updated: 2024/08/18 04:28:56 by chuhlig          ###   ########.fr       */
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

int	pwd(void)
{
	char	cwd[1028];

	getcwd(cwd, sizeof(cwd));
	printf("%s\n", cwd);
	return (0);
}

int	env(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
	return (0);
}

int	cd(char **av)
{

	if(av[1] == NULL)
	{
	while (env[i] != NULL) // home command
	{
		if (ft_strncmp(env[i], "HOME=", 5) == 0)
			break ;
		i++;
	}
	// before chdir we need to update old pwd
	// getcwd(cwd, sizeof(cwd));
	// str = ft_strjoin("PWD= or old pwd=", cwd);
	// env[i] = str;
	if(chdir(env[i] + 5) == -1)
			return;
	}
	else
		//update old pwd
		//
		while (env[i] != NULL) // home command
		{
		if (ft_strncmp(env[i], "old PWD=", 5) == 0)
			break ;
		i++;
		}
		str = ft_strjoin("old pwd=", cwd);
		env[i] = str;
		//
		chdir(av[1] ==  -1);
			return ;
	// udpate pwd
	while (env[i] != NULL) // home command
	{
		if (ft_strncmp(env[i], "PWD=", 5) == 0)
			break ;
		i++;
	}
	str = ft_strjoin("PWD=", cwd);
	env[i] = str;
}

// exit


int	exit(char *av)
{
	freenode free toke free sequence stop repl free env
	clear history
}
//joar

//export

int	export(char **av, t_env **env)
{
	char	*tmp;
	if(tmp = ft_strchr(av[1]))
	{
		tmp = '\0';
		t_env *current;
		current = *env;
		while(current)
		{
			if (strcmp(current->name, av[1]) == 0)
			{
                free(current->value);
                current->value = ft_strdup(tmp + 1);
                break;
            }
            current = current->next;
		}
		if (!current)
		{
            current = malloc(sizeof(t_env));
            current->name = ft_strdup(av[1]);
            current->value = ft_strdup(tmp + 1);
            current->next = *env;
            *env = current;
        }
		return (0);
	}
	else
		syntax return 1;
}

//unset

int	unset(char **av, t_env **env)
{
	t_env	*current;
	t_env	*prev;
	
	current = env;
	prev = NULL;
	while (current)
	{
		if(ft_strcmp(current->name, av[1] == 0))
			break ;
		prev = current;
		current = current->next;
	}
	if(current)
	{
		if(prev)
			prev->next = current->next;
		else
			*env = current->next
		free(t_env);
	}
	return (0);
}
