/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_part_one.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:01:16 by chuhlig           #+#    #+#             */
/*   Updated: 2024/10/17 14:29:40 by chuhlig          ###   ########.fr       */
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
		if(ft_strcmp(current->name, av == 0))
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

void	update_oldpwd(t_env **env)
{
	t_env	*current;
	t_env	*prev;
	char	cwd[1028];
	char	*tmp;

	while (current) // home command
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

int	cd(t_env **env,char **av)
{
	t_env	*current;
	t_env	*prev;
	t_env	*pwd;

	current = env;
	if(av[1] == NULL)
	{
		update_oldpwd(&env);
		while (current) // home command
		{
			if (ft_strncmp(current->name, "HOME", 4) == 0)
				break ;
			prev = current;
			current = current->next;
		}
		if(chdir(current->value) == -1)
			return ;
	}
	else
	{
		update_oldpwd(&env);
		if(chdir(av[1]) ==  -1)
			return ;
		update_pwd(&env);
	}
}

// exit

int	exit(char *av)
{
	freenode free toke free sequence stop repl free env
	clear history
}

//export

int	export(char **av, t_env **env)
{
	char	*tmp;
	t_env	*current;
	int		i;

	i = i;
	while(av[i])
	{
		if(tmp = ft_strchr(av[i], '='))
		{
			tmp = '\0';
			current = *env;
			while(current)
			{
				if (strcmp(current->name, av[i]) == 0)
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
    	        current->name = ft_strdup(av[i]);
    	        current->value = ft_strdup(tmp + 1);
    	        current->next = *env;
    	        *env = current;
    	    }
			return (0);
		}
		i++;
	}
	return 1;
}

//unset
//for unset as well check and for name part
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
			*env = current->next;
		free(current->value);
		free(current);
	}
	return (0);
}


// void	getenvlststr(t_env **env, char **en)//without serparation
// {
// 	int			i;
// 	size_t		t;
// 	t_env 	*current;

// 	t = 0;
// 	i = 0;
// 	while (en[i] != NULL)
// 	{
// 		current = *env;
//         current = malloc(sizeof(t_env));
// 		while(en[t] != '=')
// 			t++;
//         current->name = ft_substr(en[i], 0, t);
//         current->value = ft_strdup(en[i]);
//         current->next = *env;
//         *env = current;
// 		i++;
// 	}
// 	return (0);
// }

//should name the list different