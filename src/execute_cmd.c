/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:21:35 by chuhlig           #+#    #+#             */
/*   Updated: 2025/01/13 09:50:56 by chuhlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <stdlib.h>
#include <sys/_types/_pid_t.h>
#include <sys/_types/_s_ifmt.h>
#include <sys/fcntl.h>
#include <unistd.h>

int	execute_cmd(t_cmd *cmd, t_env **env)
{
	char	*cmd_path;
	pid_t	pid;
	int		status;
	int		result;
	int		original_stdout;
	int		original_stdin;

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
			printf("%s: command not found\n", cmd->args[0]);
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