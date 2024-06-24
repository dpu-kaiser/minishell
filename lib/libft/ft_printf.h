/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 18:19:47 by dkaiser           #+#    #+#             */
/*   Updated: 2024/06/24 16:43:56 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int	ft_printf(const char *fmt, ...);
int	ft_printnbr(int nbr);
int	ft_printunbr(unsigned int nbr);
int	ft_printhex(unsigned int nbr, char fmt);
int	ft_printaddr(void *addr);
#endif // FT_PRINTF_H
