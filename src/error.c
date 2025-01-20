/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:35:53 by dkaiser           #+#    #+#             */
/*   Updated: 2025/01/20 18:12:40 by dkaiser          ###   ########.fr       */
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

void	command_not_found_error(char *cmd)
{
	ft_printf("%s:", cmd);
	ft_putstr_fd(" command not found", 2);
	ft_printf("\n");
}
