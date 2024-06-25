/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printaddr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 10:33:53 by dkaiser           #+#    #+#             */
/*   Updated: 2024/03/18 11:42:58 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	printaddr_rec(unsigned long addr, int *len)
{
	char	c;
	int		success;

	if (*len < 0)
		return ;
	if (addr % 16 < 10)
		c = '0' + (addr % 16);
	else
		c = ('a' - 10) + (addr % 16);
	if (addr > 15)
		printaddr_rec(addr / 16, len);
	success = write(1, &c, 1);
	if (success < 0 || *len < 2)
		*len = -1;
	else
		(*len)++;
}

int	ft_printaddr(void *addr)
{
	int	len;

	len = write(1, "0x", 2);
	printaddr_rec((unsigned long)addr, &len);
	return (len);
}
