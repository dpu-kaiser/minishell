/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 18:18:59 by dkaiser           #+#    #+#             */
/*   Updated: 2024/03/18 11:42:34 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_char(char c)
{
	return (write(1, &c, 1));
}

static int	print_str(char *str)
{
	int	success;
	int	len;

	if (str)
	{
		len = 0;
		while (str[len])
			len++;
		success = write(1, str, len);
		if (success < 0)
			return (-1);
		return (len);
	}
	else
	{
		success = write(1, "(null)", 6);
		if (success == 6)
			return (6);
		return (-1);
	}
}

static int	print_conv(va_list args, char c)
{
	if (c == 'c')
		return (print_char(va_arg(args, int)));
	if (c == 's')
		return (print_str(va_arg(args, char *)));
	if (c == 'p')
		return (ft_printaddr(va_arg(args, void *)));
	if (c == 'd' || c == 'i')
		return (ft_printnbr(va_arg(args, int)));
	if (c == 'u')
		return (ft_printunbr(va_arg(args, unsigned int)));
	if (c == 'x' || c == 'X')
		return (ft_printhex(va_arg(args, unsigned int), c));
	if (c == '%')
		return (print_char('%'));
	return (-1);
}

int	ft_printf(const char *fmt, ...)
{
	int		result;
	int		last_result;
	int		success;
	va_list	args;

	result = 0;
	va_start(args, fmt);
	while (*fmt)
	{
		last_result = result;
		if (*fmt == '%')
			result += print_conv(args, *(++fmt));
		else
		{
			success = write(1, fmt, 1);
			if (success <= 0)
				return (-1);
			result++;
		}
		fmt++;
		if (result < last_result)
			return (-1);
	}
	va_end(args);
	return (result);
}
