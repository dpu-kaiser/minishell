/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:21:35 by chuhlig           #+#    #+#             */
/*   Updated: 2025/01/09 16:07:01 by chuhlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <stdlib.h>
#include <sys/_types/_pid_t.h>
#include <sys/_types/_s_ifmt.h>
#include <sys/fcntl.h>
#include <unistd.h>

// static void	format_args(char **args, t_env *env);

// int	execute_cmd(t_cmd *cmd, t_env **env)
// {
// 	int		result;
// 	char	*cmd_path;
// 	int		fd;

// 	if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
// 		return (pwd(*env));
// 	else if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
// 		return (echo(cmd->args));
// 	else if (ft_strncmp(cmd->args[0], "env", 4) == 0)
// 		return (ft_env(*env));
// 	else if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
// 		return (cd(env, cmd->args));
// 	else if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
// 		return (unset(cmd->args, env));
// 	else if (ft_strncmp(cmd->args[0], "export", 7) == 0)
// 		return (export(cmd->args, env));
// 	format_args(cmd->args, *env);
// 	cmd_path = get_cmd_path(cmd->args[0], *env);
// 	cmd->args[0] = cmd_path;
// 	if (cmd->redirs[0].type == INPUT_FILE)
// 	{
// 		fd = open(cmd->redirs[0].specifier, O_RDONLY);
// 		if (fd < 0)
// 			return (EXIT_FAILURE);
// 		dup2(fd, STDIN_FILENO);
// 	}
// 	else if (cmd->redirs[0].type == INPUT_LIMITER)
// 	{
// 		dbg("INPUT_LIMITER");
// 	}
// 	if (cmd->redirs[1].type == OUTPUT_APPEND)
// 	{
// 		dbg("OUTPUT_APPEND");
// 		fd = open(cmd->redirs[1].specifier, O_WRONLY | O_CREAT | O_APPEND, 644);
// 		if (fd < 0)
// 			return (EXIT_FAILURE);
// 		dup2(fd, STDOUT_FILENO);
// 	}
// 	else if (cmd->redirs[1].type == OUTPUT_OVERRIDE)
// 	{
// 		fd = open(cmd->redirs[1].specifier, O_WRONLY | O_CREAT | O_TRUNC, 644);
// 		if (fd < 0)
// 			return (EXIT_FAILURE);
// 		dup2(fd, STDOUT_FILENO);
// 		dbg("OUTPUT_OVERRIDE");
// 	}
// 	result = execve(cmd->args[0], cmd->args, env_to_strlst(*env));
// 	return (result);
// }

// static void	format_args(char **args, t_env *env)
// {
// 	char	*formatted;

// 	while (*args != NULL)
// 	{
// 		formatted = format_string(*args, env);
// 		/* free(*args); */
// 		*args = formatted;
// 		args++;
// 	}
// }