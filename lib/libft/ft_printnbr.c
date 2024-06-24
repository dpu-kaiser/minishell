/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:18:40 by dkaiser           #+#    #+#             */
/*   Updated: 2024/03/18 11:41:27 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	printnbr_rec(int n, int *len)
{
	char	c;
	int		success;

	if (*len < 0)
		return ;
	c = '0' + n % 10;
	if (n > 9)
		printnbr_rec(n / 10, len);
	if (*len < 0)
		return ;
	success = write(1, &c, 1);
	if (success < 0)
		*len = -1;
	else
		(*len)++;
}

int	ft_printnbr(int nbr)
{
	int	len;

	len = 0;
	if (nbr == -2147483648)
		return (write(1, "-2147483648", 11));
	if (nbr < 0)
	{
		len = write(1, "-", 1);
		nbr *= -1;
	}
	printnbr_rec(nbr, &len);
	if (len < 0)
		return (-1);
	return (len);
}

static void	printunbr_rec(unsigned int n, int *len)
{
	char	c;
	int		success;

	if (*len < 0)
		return ;
	c = '0' + n % 10;
	if (n > 9)
		printunbr_rec(n / 10, len);
	if (*len < 0)
		return ;
	success = write(1, &c, 1);
	if (success < 0)
		*len = -1;
	else
		(*len)++;
}

int	ft_printunbr(unsigned int nbr)
{
	int	len;

	len = 0;
	printunbr_rec(nbr, &len);
	if (len < 0)
		return (-1);
	return (len);
}
