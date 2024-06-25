/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 10:42:08 by dkaiser           #+#    #+#             */
/*   Updated: 2024/03/10 13:18:58 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_last_digit(int n)
{
	int	last_digit;

	last_digit = n % 10;
	if (last_digit < 0)
		last_digit *= -1;
	return (last_digit);
}

static int	get_len(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		len++;
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		len;

	len = get_len(n);
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (0);
	result[len] = '\0';
	if (n == 0)
		result[0] = '0';
	if (n < 0)
		result[0] = '-';
	while (n)
	{
		result[--len] = '0' + get_last_digit(n);
		n /= 10;
	}
	return (result);
}

/* #include <stdio.h> */
/* int main() { */
/*     char* itoa = ft_itoa(0); */
/*     printf("%s\n", itoa); */
/* } */
