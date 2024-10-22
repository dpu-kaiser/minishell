/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:58:56 by dkaiser           #+#    #+#             */
/*   Updated: 2024/10/22 15:42:17 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <sys/_types/_pid_t.h>
#include <unistd.h>

int	execute_cmd(t_cmd *cmd, t_env *env)
{
	int		result;
	char	*cmd_path;

	cmd_path = get_cmd_path(cmd->args[0], env);
	cmd->args[0] = cmd_path;
	result = execve(cmd->args[0], cmd->args, env_to_strlst(env));
	return (result);
}
