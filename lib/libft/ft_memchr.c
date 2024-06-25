/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:23:01 by dkaiser           #+#    #+#             */
/*   Updated: 2024/03/10 13:16:25 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (*((unsigned char *)s + i) == (unsigned char)c)
			return ((void *)s + i);
		i++;
	}
	return (0);
}

/* #include <stdio.h> */
/* int main () { */
/*     char str[] = "Hello world"; */
/*     printf("memchr: %s\n", (char *) memchr(str, 'o', 11)); */
/*     printf("ft_memchr: %s\n", (char *) ft_memchr(str, 'o', 11)); */
/* } */
