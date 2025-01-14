/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:21:35 by chuhlig           #+#    #+#             */
/*   Updated: 2025/01/14 16:56:24 by chuhlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	return ((ft_strcmp(cmd, "export") == 0)
		|| (ft_strcmp(cmd, "unset") == 0)
		|| (ft_strcmp(cmd, "cd") == 0)
		|| (ft_strcmp(cmd, "exit") == 0)
		|| (ft_strcmp(cmd, "echo") == 0)
		|| (ft_strcmp(cmd, "pwd") == 0)
		|| (ft_strcmp(cmd, "env") == 0));
}

int	execute_builtin(char **args, t_env **env)
{
	if (ft_strcmp(args[0], "export") == 0)
		return (export(args, env));
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
	char	*cmd_path;
	pid_t	pid;
	int		status;
	int		original_stdout;
	int		original_stdin;
	int		result;

	original_stdout = dup(STDOUT_FILENO);
	original_stdin = dup(STDIN_FILENO);
	if (handle_redirections(cmd->redirs) == -1)
	{
		dup2(original_stdout, STDOUT_FILENO);
		dup2(original_stdin, STDIN_FILENO);
		close(original_stdout);
		close(original_stdin);
		return (EXIT_FAILURE);
	}
	if (is_builtin(cmd->args[0]))
	{
		result = execute_builtin(cmd->args, env);
		dup2(original_stdout, STDOUT_FILENO);
		dup2(original_stdin, STDIN_FILENO);
		close(original_stdout);
		close(original_stdin);
		return (result);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		dup2(original_stdout, STDOUT_FILENO);
		dup2(original_stdin, STDIN_FILENO);
		close(original_stdout);
		close(original_stdin);
		return (EXIT_FAILURE);
	}
	if (pid == 0)
	{
		cmd_path = get_cmd_path(cmd->args[0], *env);
		if (!cmd_path)
		{
			printf("command not found\n");
			exit(EXIT_FAILURE);
		}
		execve(cmd_path, cmd->args, env_to_strlst(*env));
		perror("execve");
		exit(EXIT_FAILURE);
	}
	waitpid(pid, &status, 0);
	dup2(original_stdout, STDOUT_FILENO);
	dup2(original_stdin, STDIN_FILENO);
	close(original_stdout);
	close(original_stdin);
	return (WEXITSTATUS(status));
}
