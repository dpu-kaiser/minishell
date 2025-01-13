/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 16:53:39 by dkaiser           #+#    #+#             */
/*   Updated: 2024/12/24 16:21:50 by chuhlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H
# include "libft.h"
# include <stdio.h>

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

void	getenvlst(t_env **env, char **en);
void	free_envlst(t_env **env);
char	*env_get(t_env *env, char *name);
char	**env_to_strlst(t_env *env);
void	update_oldpwd(t_env **env);
void	update_pwd(t_env **env);
int		unset(char **av, t_env **env);
int		export(char **av, t_env **env);
int		echo(char **av);
int		pwd(t_env *env);
int		cd(t_env **env, char **args);
int		ft_env(t_env *env);

#endif