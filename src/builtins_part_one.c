/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_part_one.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:01:16 by chuhlig           #+#    #+#             */
/*   Updated: 2024/09/04 17:52:49 by chuhlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	echo(char **av)//more or less done
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


int	pwd(t_env **env, char *av) //done
{
	t_env	*current;
	t_env	*prev;
	char	*tmp;

	current = env;
	prev = NULL;
	while (current)
	{
		if(ft_strcmp(current->name, av == 0))
			break ;
		prev = current;
		current = current->next;
	}
	ft_printf("%s\n", current->value);
	return (0);
}

int	env(t_env **env)// here i need str env oder ich print es alles zusammen xD
{
	t_env	*current;
	t_env	*prev;
	char	*tmp;

	current = env;
	prev = NULL;
	while (current)
	{
		ft_printf("%s\n", current->name);
		prev = current;
		current = current->next;
	}
	return (0);
}

int	cd(t_env **env,char **av) // here also need to do the same again for envstrarr. dont like it
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

int	export(char **av, t_env **env) // here also need to do the same again for envstrarr. dont like it
{
	char	*tmp;
	if(tmp = ft_strchr(av[1], '='))
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
//for unset as well check and for name part
int	unset(char **av, t_env **env) // here also need to do the same again for envstrarr. dont like it
{
	t_env	*current;
	t_env	*prev;
	char	*tmp;

	current = env;
	prev = NULL;
	tmp = ft_strchr(av[1], '=');
	tmp = '\0';
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
		free(t_env);//need function for this
	}
	return (0);
}

void	getenvlst(t_env **env, char **en)// seperated name and value
{
	char	*tmp;
	int		i;
	t_env 	*current;

	i = 0;
	while (en[i] != NULL)
	{
		tmp = ft_strchr(en[i], '=');
		tmp = '\0';
		current = *env;
        current = malloc(sizeof(t_env));
        current->name = ft_strdup(en[i]);
        current->value = ft_strdup(tmp + 1);
        current->next = *env;
        *env = current;
		i++;
	}
	return (0);
}

void	getenvlststr(t_env **env, char **en)//without serparation
{
	int			i;
	size_t		t;
	t_env 	*current;

	t = 0;
	i = 0;
	while (en[i] != NULL)
	{
		current = *env;
        current = malloc(sizeof(t_env));
		while(en[t] != '=')
			t++;
        current->name = ft_substr(en[i], 0, t);
        current->value = ft_strdup(en[i]);
        current->next = *env;
        *env = current;
		i++;
	}
	return (0);
}

//should name the list different