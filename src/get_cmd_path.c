/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:19:59 by chuhlig           #+#    #+#             */
/*   Updated: 2025/01/15 14:33:58 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <errno.h>
#include <sys/errno.h>
#include <sys/unistd.h>
#include <unistd.h>

static char	*get_absolute_cmd_path(char *cmd, t_env *env, int *return_code);
static char	*find_in_path(char *cmd, t_env *env, int *return_code);
char		**get_split_path(t_env *env);

char	*get_cmd_path(char *cmd, t_env *env, int *return_code)
{
	char *result;

	if (cmd[0] == '/')
	{
		result = ft_strdup(cmd);
		if (access(result, F_OK) == -1)
		{
			free(result);
			errno = ENOENT;
			perror(cmd);
			*return_code = 127;
			return (NULL);
		}
		else if (access(result, X_OK) == -1)
		{
			free(result);
			errno = EACCES;
			perror(cmd);
			*return_code = 126;
			return (NULL);
		}
		return (result);
	}
	else if (ft_strchr(cmd, '/'))
		return (get_absolute_cmd_path(cmd, env, return_code));
	else
		return (find_in_path(cmd, env, return_code));
}

static char	*get_absolute_cmd_path(char *cmd, t_env *env, int *return_code)
{
	char	*cur_dir;
	char	*result;

	cur_dir = ft_strjoin(env_get(env, "PWD"), "/");
	if (!cur_dir)
		return (NULL);
	result = ft_strjoin(cur_dir, cmd);
	free(cur_dir);
	if (!result)
	{
		*return_code = 127;
		errno = ENOENT;
		perror(cmd);
		return (NULL);
	}
	if (access(result, F_OK) == -1)
	{
		free(result);
		errno = ENOENT;
		*return_code = 127;
		perror(cmd);
		return (NULL);
	}
	if (access(result, X_OK) == -1)
	{
		free(result);
		errno = EACCES;
		*return_code = 126;
		perror(cmd);
		return (NULL);
	}
	return (result);
}

static char	*find_in_path(char *cmd, t_env *env, int *return_code)
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
	*return_code = 127;
	printf("%s:", cmd);
	ft_putstr_fd(" command not found", 2);
	return (NULL);
}

char	**get_split_path(t_env *env)
{
	char	*path;

	path = env_get(env, "PATH");
	return (ft_split(path, ':'));
}
