/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:19:59 by chuhlig           #+#    #+#             */
/*   Updated: 2024/12/17 19:20:08 by chuhlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static char	*get_absolute_cmd_path(char *cmd, t_env *env);
static char	*find_in_path(char *cmd, t_env *env);
char		**get_split_path(t_env *env);

char	*get_cmd_path(char *cmd, t_env *env)
{
	if (cmd[0] == '/')
		return (ft_strdup(cmd));
	else if (ft_strchr(cmd, '/'))
		return (get_absolute_cmd_path(cmd, env));
	else
		return (find_in_path(cmd, env));
}

static char	*get_absolute_cmd_path(char *cmd, t_env *env)
{
	char	*cur_dir;
	char	*result;

	cur_dir = ft_strjoin(env_get(env, "PWD"), "/");
	if (!cur_dir)
		return (NULL);
	result = ft_strjoin(cur_dir, cmd);
	free(cur_dir);
	if (!result)
		return (NULL);
	if (access(result, X_OK) == -1)
	{
		free(result);
		return (NULL);
	}
	return (result);
}

static char	*find_in_path(char *cmd, t_env *env)
{
	char	*cur_path;
	char	*cmd_path;
	char	**path;

	path = get_split_path(env);
	cmd_path = NULL;
	while (*path)
	{
		if (cmd_path)
			free(cmd_path);
		cur_path = ft_strjoin(*path, "/");
		if (!cur_path)
			return (NULL);
		cmd_path = ft_strjoin(cur_path, cmd);
		free(cur_path);
		if (!cmd_path)
			return (NULL);
		if (access(cmd_path, X_OK) != -1)
			return (cmd_path);
		path++;
	}
	return (NULL);
}

char	**get_split_path(t_env *env)
{
	char	*path;

	path = env_get(env, "PATH");
	return (ft_split(path, ':'));
}
