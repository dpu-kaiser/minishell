/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug-tools.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:34:37 by dkaiser           #+#    #+#             */
/*   Updated: 2024/06/24 18:35:48 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

# ifndef DEBUG
#  define DEBUG 0
# endif

void	dbg(char *str);
void	panic(char *msg);
