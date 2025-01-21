/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_tools.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:34:37 by dkaiser           #+#    #+#             */
/*   Updated: 2025/01/20 19:38:02 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_TOOLS_H
# define DEBUG_TOOLS_H
# include "libft.h"
# include <stdarg.h>

# ifndef DEBUG
#  define DEBUG 0
# endif
# define UNREACHABLE "Unreachable."

void	dbg(char *str);
void	panic(char *msg);

#endif
