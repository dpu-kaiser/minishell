/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:15:49 by chuhlig           #+#    #+#             */
/*   Updated: 2025/01/11 12:52:57 by chuhlig          ###   ########.fr       */
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


// static int	eval_rec(t_node *node, t_env **env, int in_fd);

// int	eval(t_node *node, t_env **env)
// {
// 	pid_t	pid;
// 	int		result;

// 	if (node == NULL)
// 		return (EXIT_FAILURE);
// 	result = 0;
// 	pid = fork();
// 	if (pid < 0)
// 	{
// 		return (EXIT_FAILURE);
// 	}
// 	if (pid == 0)
// 	{
// 		result = eval_rec(node, env, STDIN_FILENO);
// 		exit(result);
// 	}
// 	else
// 	{
// 		waitpid(pid, &result, 0);
// 	}
// 	return (result);
// }

// static int	eval_rec(t_node *node, t_env **env, int in_fd)
// {
// 	pid_t	pid;
// 	int		result;
// 	int		p[2];

// 	result = pipe(p);
// 	if (result == -1)
// 		return (EXIT_FAILURE);
// 	if (node->type == PIPE_NODE)
// 	{
// 		pid = fork();
// 		if (pid < 0)
// 		{
// 			return (EXIT_FAILURE);
// 		}
// 		if (pid == 0)
// 		{
// 			close(p[0]);
// 			dup2(in_fd, STDIN_FILENO);
// 			dup2(p[1], STDOUT_FILENO);
// 			result = execute_cmd(&node->content.pipe.left->content.cmd, env);
// 			exit(result);
// 		}
// 		else
// 		{
// 			close(p[1]);
// 			dup2(p[0], STDIN_FILENO);
// 			result = eval_rec(node->content.pipe.right, env, p[0]);
// 		}
// 	}
// 	else if (node->type == CMD_NODE)
// 	{
// 		result = execute_cmd(&node->content.cmd, env);
// 	}
// 	else
// 	{
// 		panic(UNREACHABLE);
// 		return (EXIT_FAILURE);
// 	}
// 	return (result);
// }


//old interpreter
// #include "minishell.h"
// #include <stdio.h>

// static int	eval_pipe(t_pipe *pipe, t_env *env);
// static int	eval_cmd(t_cmd *cmd, t_env **env);

// int	eval(t_node *node, t_env **env)
// {
// 	if (node->type == PIPE_NODE)
// 		return (eval_pipe(&node->content.pipe, *env));
// 	else if (node->type == CMD_NODE)
// 		return (eval_cmd(&node->content.cmd, env));
// 	else
// 	{
// 		panic(UNREACHABLE);
// 		return (-1);
// 	}
// }

// static int	eval_pipe(t_pipe *pipe, t_env *env)
// {
// 	dbg("TODO: PIPE");
// 	eval_cmd(&pipe->left->content.cmd, &env);
// 	eval_cmd(&pipe->right->content.cmd, &env);
// 	return (0);
// }

// static int	eval_cmd(t_cmd *cmd, t_env **env)
// {
// 	if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
// 		pwd(*env);
// 	else if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
// 		echo(cmd->args);
// 	else if (ft_strncmp(cmd->args[0], "env", 4) == 0)
// 		ft_env(*env);
// 	else if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
// 		cd(env, cmd->args);
// 	else if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
// 		unset(cmd->args, env);
// 	else if (ft_strncmp(cmd->args[0], "export", 7) == 0)
// 		export(cmd->args, env);
// 	return (0);
// }

//v2.0

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
// v1.0

// static int	handle_redirections(t_redirection *redirs)
// {
// 	int	fd;
// 	int	pipe_fds[2];

// 	if (redirs[0].type == INPUT_LIMITER)
// 	{
// 		if (pipe(pipe_fds) == -1)
// 		{
// 			perror("pipe");
// 			return (-1);
// 		}
// 		write(pipe_fds[1], redirs[0].specifier, strlen(redirs[0].specifier));
// 		close(pipe_fds[1]);
// 		dup2(pipe_fds[0], STDIN_FILENO);
// 		close(pipe_fds[0]);
// 	}
// 	else if (redirs[0].type == INPUT_FILE)
// 	{
// 		fd = open(redirs[0].specifier, O_RDONLY);
// 		if (fd == -1)
// 		{
// 			perror(redirs[0].specifier);
// 			return (-1);
// 		}
// 		dup2(fd, STDIN_FILENO);
// 		close(fd);
// 	}
// 	if (redirs[1].type == OUTPUT_OVERRIDE)
// 	{
// 		fd = open(redirs[1].specifier, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 		if (fd == -1)
// 		{
// 			perror(redirs[1].specifier);
// 			return (-1);
// 		}
// 		dup2(fd, STDOUT_FILENO);
// 		close(fd);
// 	}
// 	else if (redirs[1].type == OUTPUT_APPEND)
// 	{
// 		fd = open(redirs[1].specifier, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 		if (fd == -1)
// 		{
// 			perror(redirs[1].specifier);
// 			return (-1);
// 		}
// 		dup2(fd, STDOUT_FILENO);
// 		close(fd);
// 	}
// 	return (0);
// }
//v 3.0
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
        // Handle here document (<<)
        // Assuming heredoc_data is stored in redirs[0].specifier
        fd = open("/tmp/heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd < 0)
        {
            perror("open");
            return (-1);
        }
        write(fd, redirs[0].specifier, strlen(redirs[0].specifier));
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
//v 2.0
// static int	eval_rec(t_node *node, t_env **env, int in_fd)
// {
// 	pid_t	pid;
// 	int		p[2];
// 	int		result;
// 	int		status;

// 	if (node->type == PIPE_NODE)
// 	{
// 		pipe(p);
// 		pid = fork();
// 		if (pid == 0)
// 		{
// 			close(p[0]);
// 			dup2(in_fd, STDIN_FILENO);
// 			dup2(p[1], STDOUT_FILENO);
// 			result = eval_rec(node->content.pipe.left, env, in_fd);
// 			exit(result);
// 		}
// 		else
// 		{
// 			close(p[1]);
// 			dup2(p[0], STDIN_FILENO);
// 			result = eval_rec(node->content.pipe.right, env, p[0]);
// 			waitpid(pid, &status, 0);
// 		}
// 	}
// 	else if (node->type == CMD_NODE)
// 	{
// 		result = execute_cmd(&node->content.cmd, env);
// 	}
// 	else
// 	{
// 		panic("UNREACHABLE");
// 		result = EXIT_FAILURE;
// 	}
// 	return (result);
// }

//v 3.0

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
//v was auch immmer 

// int	execute_cmd(t_cmd *cmd, t_env **env)
// {
// 	char	*cmd_path;
// 	pid_t	pid;
// 	int status;

// 	if (handle_redirections(cmd->redirs) == -1)
// 	{
// 		return (EXIT_FAILURE);
// 	}
// 	if (is_builtin(cmd->args[0]))
// 	{
// 		return (execute_builtin(cmd->args, env));
// 	}
// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		perror("fork");
// 		return (EXIT_FAILURE);
// 	}
// 	if (pid == 0)
// 	{
// 		cmd_path = get_cmd_path(cmd->args[0], *env);
// 		if (!cmd_path)
// 		{
// 			printf("%s: command not found\n", cmd->args[0]);
// 			return (EXIT_FAILURE);
// 		}
// 		execve(cmd_path, cmd->args, env_to_strlst(*env));
// 		perror("execve");
// 		exit(EXIT_FAILURE);
// 	}
// 	waitpid(pid, &status, 0);
// 	return (WEXITSTATUS(status));
// }
int	execute_cmd(t_cmd *cmd, t_env **env)
{
    char	*cmd_path;
    pid_t	pid;
    int		status;
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
        int result = execute_builtin(cmd->args, env);
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