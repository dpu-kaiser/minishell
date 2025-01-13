/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:15:49 by chuhlig           #+#    #+#             */
/*   Updated: 2025/01/13 09:53:33 by chuhlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug_tools.h"
#include "minishell.h"
#include <stdlib.h>
#include <sys/_types/_pid_t.h>
#include <sys/cdefs.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <sys/types.h>

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
	else if (ft_strcmp(args[0], "exit") == 0)
		return (EXIT_SUCCESS);
	else if (ft_strcmp(args[0], "echo") == 0)
		return (echo(args));
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (pwd(*env));
	else if (ft_strcmp(args[0], "env") == 0)
		return (ft_env(*env));
	return (1);
}

static int	handle_redirections(t_redirection *redirs)
{
	int	fd;

	if (redirs[0].type == INPUT_FILE)
	{
		fd = open(redirs[0].specifier, O_RDONLY);
		if (fd < 0)
		{
			perror("open");
			return (-1);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (redirs[0].type == INPUT_LIMITER)
	{
		fd = open("/tmp/heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			perror("open");
			return (-1);
		}
		write(fd, redirs[0].specifier, ft_strlen(redirs[0].specifier));
		close(fd);
		fd = open("/tmp/heredoc_tmp", O_RDONLY);
		if (fd < 0)
		{
			perror("open");
			return (-1);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (redirs[1].type == OUTPUT_OVERRIDE)
	{
		fd = open(redirs[1].specifier, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			perror("open");
			return (-1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (redirs[1].type == OUTPUT_APPEND)
	{
		fd = open(redirs[1].specifier, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
		{
			perror("open");
			return (-1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (0);
	}

static int	eval_rec(t_node *node, t_env **env, int in_fd)
{
	pid_t	pid;
	int		p[2];
	int		result;
	int		status;
	int		original_stdin;

	if (node->type == PIPE_NODE)
	{
		pipe(p);
		pid = fork();
		if (pid == 0)
		{
			close(p[0]);
			dup2(in_fd, STDIN_FILENO);
			dup2(p[1], STDOUT_FILENO);
			result = eval_rec(node->content.pipe.left, env, in_fd);
			exit(result);
		}
		else
		{
			close(p[1]);
			original_stdin = dup(STDIN_FILENO);
			dup2(p[0], STDIN_FILENO);
			result = eval_rec(node->content.pipe.right, env, p[0]);
			waitpid(pid, &status, 0);
			dup2(original_stdin, STDIN_FILENO);
			close(original_stdin);
		}
	}
	else if (node->type == CMD_NODE)
	{
		result = execute_cmd(&node->content.cmd, env);
	}
	else
	{
		printf("Handling unknown node type\n");
		panic("UNREACHABLE");
		result = EXIT_FAILURE;
	}
	return (result);
}

int eval(t_node *node, t_env **env)
{
	return (eval_rec(node, env, STDIN_FILENO));
}
