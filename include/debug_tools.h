/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_tools.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:34:37 by dkaiser           #+#    #+#             */
/*   Updated: 2025/01/23 15:22:14 by chuhlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_TOOLS_H
# define DEBUG_TOOLS_H
# include "libft.h"
# include <stdarg.h>
# include "token.h"

# ifndef DEBUG
#  define DEBUG 0
# endif
# define UNREACHABLE "Unreachable."

void	dbg(char *str);
void	panic(char *msg);

void	print_token_list(t_token *token_list);


#endif
