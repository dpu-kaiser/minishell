/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:19:59 by chuhlig           #+#    #+#             */
/*   Updated: 2025/01/20 18:12:33 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <errno.h>
#include <sys/errno.h>
#include <sys/stat.h>
#include <sys/unistd.h>
#include <unistd.h>

static char	*get_simple_cmd_path(char *cmd, int *return_code);
static char	*get_absolute_cmd_path(char *cmd, t_env *env, int *return_code);
static char	*find_in_path(char *cmd, t_env *env, int *return_code);
char		**get_split_path(t_env *env);
static int	is_directory(char *path);

char	*get_cmd_path(char *cmd, t_env *env, int *return_code)
{
	if (cmd[0] == '/')
		return (get_simple_cmd_path(cmd, return_code));
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
		return (error(ENOENT, cmd, 127, return_code));
	if (access(result, F_OK) == -1)
	{
		free(result);
		return (error(ENOENT, cmd, 127, return_code));
	}
	if (access(result, X_OK) == -1)
	{
		free(result);
		return (error(EACCES, cmd, 126, return_code));
	}
	if (is_directory(cmd))
		return (error(EISDIR, cmd, 126, return_code));
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
	command_not_found_error(cmd);
	return (NULL);
}

static char	*get_simple_cmd_path(char *cmd, int *return_code)
{
	char	*result;

	result = ft_strdup(cmd);
	if (access(result, F_OK) == -1)
	{
		free(result);
		return (error(ENOENT, cmd, 127, return_code));
	}
	else if (access(result, X_OK) == -1)
	{
		free(result);
		return (error(EACCES, cmd, 126, return_code));
	}
	if (is_directory(cmd))
		return (error(EISDIR, cmd, 126, return_code));
	return (result);
}

static int	is_directory(char *path)
{
	struct stat	path_stat;

	stat(path, &path_stat);
	if ((path_stat.st_mode & S_IFMT) == S_IFDIR)
		return (1);
	else
		return (0);
}
