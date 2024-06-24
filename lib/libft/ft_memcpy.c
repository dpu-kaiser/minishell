/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:15:12 by dkaiser           #+#    #+#             */
/*   Updated: 2024/03/10 13:14:24 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*dst_ptr;
	char	*src_ptr;

	dst_ptr = (char *)dst;
	src_ptr = (char *)src;
	if (!dst && !src)
		return (dst);
	while (n--)
		*dst_ptr++ = *src_ptr++;
	return (dst);
}

/* #include <stdio.h> */
/* int main(void) */
/* { */
/*     char src[] = "a"; */
/*     char src2[] = "a"; */
/*     char dst[] = ""; */
/*     char dst2[] = ""; */
/*     printf("ft_memcpy: %s\n", (char *) ft_memcpy(dst, src, 20)); */
/*     printf("memcpy: %s\n", (char *) memcpy(dst2, src2, 20)); */
/* } */
