/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:58:19 by dkaiser           #+#    #+#             */
/*   Updated: 2024/07/11 23:52:13 by chuhlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((char *)b)[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

/* #include <stdio.h> */

/* int	main(void) */
/* { */
/* 	char	str[] = "Hello world"; */

/* 	printf("STR: %s\n", str); */
/* 	printf("ft_memset: %s\n", ft_memset((char *)str, 'A' + 255, 5)); */
/* 	printf("memset: %s\n", memset((char *)str, 'A' + 255, 5)); */
/* } */

// void	*ft_memset(void *b, int c, size_t len)
// {
// 	void	*savearg;

// 	savearg = b;
// 	while (len--)
// 		*(unsigned char *)b++ = (unsigned char)c;
// 	return (savearg);
// }