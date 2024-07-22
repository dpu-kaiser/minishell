/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_tools.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:34:37 by dkaiser           #+#    #+#             */
/*   Updated: 2024/07/22 17:14:43 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_TOOLS_H
# define DEBUG_TOOLS_H

# include "libft.h"

# ifndef DEBUG
#  define DEBUG 1
# endif
# define UNREACHABLE "Unreachable."

void	dbg(char *str);
void	panic(char *msg);
#endif
