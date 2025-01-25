/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:35:53 by dkaiser           #+#    #+#             */
/*   Updated: 2025/01/25 14:58:52 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

void	*error(int err_code, char *err_text, int exit_code, int *ret_code)
{
	errno = err_code;
	perror(err_text);
	if (ret_code != NULL)
		*ret_code = exit_code;
	return (NULL);
}

void	*command_not_found_error(char *cmd, int *return_code, char *cmd_path,
		char **split_path)
{
	ft_printf("%s:", cmd);
	ft_putstr_fd(" command not found", 2);
	ft_printf("\n");
	*return_code = 127;
	free(cmd_path);
	ft_free_split(split_path);
	return (NULL);
}
