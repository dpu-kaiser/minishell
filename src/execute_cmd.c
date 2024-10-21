/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:58:56 by dkaiser           #+#    #+#             */
/*   Updated: 2024/10/21 15:07:37 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <sys/_types/_pid_t.h>
#include <unistd.h>

int	execute_cmd(t_cmd *cmd, t_env *env)
{
	int		result;
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (EXIT_FAILURE);
	if (pid == 0)
	{
		result = execve(cmd->args[0], cmd->args, env_to_strlst(env));
		exit(result);
	}
	else
	{
		// only wait if cmd is on rightmost side of pipe?
		// so in cmd1 | cmd2 | cmd3 | cmd4 only wait for cmd4
		waitpid(pid, &result, 0);
	}
	return (result);
}
