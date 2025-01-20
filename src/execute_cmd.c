/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:21:35 by chuhlig           #+#    #+#             */
/*   Updated: 2025/01/20 15:43:41 by chuhlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

static void	establish_pipeline(int original_stdin, int original_stdout);
static int	exec_cmd(t_cmd *cmd, t_env **env, int original_std[2], int result);

int	is_builtin(char *cmd)
{
	return ((ft_strcmp(cmd, "export") == 0) || (ft_strcmp(cmd, "unset") == 0)
		|| (ft_strcmp(cmd, "cd") == 0) || (ft_strcmp(cmd, "exit") == 0)
		|| (ft_strcmp(cmd, "echo") == 0) || (ft_strcmp(cmd, "pwd") == 0)
		|| (ft_strcmp(cmd, "env") == 0));
}

int	execute_builtin(char **args, t_env **env)
{
	if (ft_strcmp(args[0], "export") == 0)
		return (export(args, env, ft_atoi("0")));
	else if (ft_strcmp(args[0], "unset") == 0)
		return (unset(args, env));
	else if (ft_strcmp(args[0], "cd") == 0)
		return (cd(env, args));
	else if (ft_strcmp(args[0], "echo") == 0)
		return (echo(args));
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (pwd(*env));
	else if (ft_strcmp(args[0], "env") == 0)
		return (ft_env(*env));
	else if (ft_strcmp(args[0], "exit") == 0)
		return (builtin_exit(args, env));
	return (1);
}

int	execute_cmd(t_cmd *cmd, t_env **env)
{
	int	original_std[2];
	int	result;

	original_std[1] = dup(STDOUT_FILENO);
	original_std[0] = dup(STDIN_FILENO);
	result = create_files(cmd->create_files);
	if (result != EXIT_SUCCESS || handle_redirections(cmd->redirs) == -1)
	{
		establish_pipeline(original_std[0], original_std[1]);
		return (EXIT_FAILURE);
	}
	if (is_builtin(cmd->args[0]))
	{
		result = execute_builtin(cmd->args, env);
		establish_pipeline(original_std[0], original_std[1]);
		return (result);
	}
	if (result != EXIT_SUCCESS)
		return (result);
	return (exec_cmd(cmd, env, original_std, EXIT_SUCCESS));
}

static void	establish_pipeline(int original_stdin, int original_stdout)
{
	dup2(original_stdout, STDOUT_FILENO);
	dup2(original_stdin, STDIN_FILENO);
	close(original_stdout);
	close(original_stdin);
}

static int	exec_cmd(t_cmd *cmd, t_env **env, int original_std[2], int result)
{
	int		i;
	int		status;
	char	*cmd_path;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		establish_pipeline(original_std[0], original_std[1]);
		return (EXIT_FAILURE);
	}
	if (pid == 0)
	{
		i = 0;
		while (cmd->args[i][0] == '\0')
			i++;
		cmd_path = get_cmd_path(cmd->args[i], *env, &result);
		if (cmd_path != NULL)
			execve(cmd_path, &(cmd->args[i]), env_to_strlst(*env));
		exit(result);
	}
	waitpid(pid, &status, 0);
	establish_pipeline(original_std[0], original_std[1]);
	return (WEXITSTATUS(status));
}
