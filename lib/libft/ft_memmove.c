/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:41:44 by dkaiser           #+#    #+#             */
/*   Updated: 2024/03/10 13:14:38 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (!dst && !src)
		return (dst);
	if (dst > src)
	{
		i = len;
		while (i-- > 0)
		{
			*((char *)dst + i) = *((char *)src + i);
		}
	}
	else
	{
		i = 0;
		while (i < len)
		{
			*((char *)dst + i) = *((char *)src + i);
			i++;
		}
	}
	return (dst);
}

/* #include <stdio.h> */

/* int	main(void) */
/* { */
/* 	char	text[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; */
/* 	char	text2[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; */

/* 	printf("memmove: %s\n", memmove(text + 5, text, 5)); */
/* 	printf("ft_memmove: %s\n", ft_memmove(text2 + 5, text2, 5)); */
/* } */
