/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:58:56 by dkaiser           #+#    #+#             */
/*   Updated: 2024/10/25 20:59:22 by chuhlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <sys/_types/_pid_t.h>
#include <sys/_types/_s_ifmt.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <fcntl.h>

int	execute_cmd(t_cmd *cmd, t_env *env)
{
	int		result;
	char	*cmd_path;
	int fd;

	cmd_path = get_cmd_path(cmd->args[0], env);
	cmd->args[0] = cmd_path;

	if (cmd->redirs[0].type == INPUT_FILE)
	{
		fd = open(cmd->redirs[0].specifier, O_RDONLY);
		if (fd < 0)
			return (EXIT_FAILURE);
		dup2(fd, STDIN_FILENO);
	}
	else if (cmd->redirs[0].type == INPUT_LIMITER)
	{
		dbg("INPUT_LIMITER");
	}
	if (cmd->redirs[1].type == OUTPUT_APPEND)
	{
		dbg("OUTPUT_APPEND");
		fd = open(cmd->redirs[1].specifier, O_WRONLY | O_CREAT | O_APPEND);
		if (fd < 0)
			return (EXIT_FAILURE);
		dup2(fd, STDOUT_FILENO);
	}
	else if (cmd->redirs[1].type == OUTPUT_OVERRIDE)
	{
		fd = open(cmd->redirs[1].specifier, O_WRONLY | O_CREAT | O_TRUNC);
		if (fd < 0)
			return (EXIT_FAILURE);
		dup2(fd, STDOUT_FILENO);
		dbg("OUTPUT_OVERRIDE");
	}
	result = execve(cmd->args[0], cmd->args, env_to_strlst(env));
	return (result);
}

static int	eval_cmd(t_cmd *cmd, t_env **env)
{
	if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		pwd(*env);
	else if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		echo(cmd->args);
	else if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		ft_env(*env);
	else if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		cd(env, cmd->args);
	else if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
		unset(cmd->args, env);
	else if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		export(cmd->args, env);
	return (0);
}