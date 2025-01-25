/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:34:14 by dkaiser           #+#    #+#             */
/*   Updated: 2025/01/25 11:39:59 by chuhlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug_tools.h"
#include <stdio.h>
#include <stdarg.h>
#include "token.h"
#include <stdio.h>

void	dbg(char *msg)
{
	if (DEBUG)
	{
		ft_putstr_fd("\e[33m[DEBUG] ", 0);
		ft_putstr_fd(msg, 0);
		ft_putendl_fd("\e[0m", 0);
	}
}

void	panic(char *msg)
{
	if (DEBUG)
	{
		ft_putstr_fd("\e[31m[PANIC] ", 1);
		ft_putstr_fd(msg, 1);
		ft_putendl_fd("\e[0m", 1);
	}
}
