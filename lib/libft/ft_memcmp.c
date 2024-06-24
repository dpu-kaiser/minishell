/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:54:13 by dkaiser           #+#    #+#             */
/*   Updated: 2024/03/10 13:13:54 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	int		result;

	i = 0;
	result = 0;
	while (!result && i < n)
	{
		result = *((unsigned char *)s1 + i) - *((unsigned char *)s2 + i);
		i++;
	}
	return (result);
}

/* #include <stdio.h> */

/* int	main(void) */
/* { */
/* 	char	str1[] = "Hello"; */
/* 	char	str2[] = "Hellu"; */

/* 	printf("memcmp: %d\n", memcmp(str1, str2, 5)); */
/* 	printf("ft_memcmp: %d\n", ft_memcmp(str1, str2, 5)); */
/* } */
