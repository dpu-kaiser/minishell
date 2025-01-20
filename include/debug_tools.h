/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_tools.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:34:37 by dkaiser           #+#    #+#             */
/*   Updated: 2025/01/19 21:08:15 by chuhlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_TOOLS_H
# define DEBUG_TOOLS_H
# include <stdarg.h>
# include "debug_tools.h"

# include "libft.h"

# ifndef DEBUG
#  define DEBUG 0
# endif
# define UNREACHABLE "Unreachable."

void	dbg(char *str);
void	panic(char *msg);


void	dbg2(const char *format, ...);


#endif
