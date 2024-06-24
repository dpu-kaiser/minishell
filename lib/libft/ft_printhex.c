/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:50:35 by dkaiser           #+#    #+#             */
/*   Updated: 2024/03/18 11:42:46 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	printhex_rec(unsigned int nbr, char fmt, int *len)
{
	char	c;
	int		success;

	if (*len < 0)
		return ;
	if (nbr % 16 < 10)
		c = '0' + (nbr % 16);
	else
		c = (fmt - 33) + (nbr % 16);
	if (nbr > 15)
		printhex_rec(nbr / 16, fmt, len);
	if (*len < 0)
		return ;
	success = write(1, &c, 1);
	if (success < 0)
		*len = -1;
	else
		(*len)++;
}

int	ft_printhex(unsigned int nbr, char fmt)
{
	int	len;

	len = 0;
	printhex_rec(nbr, fmt, &len);
	return (len);
}
