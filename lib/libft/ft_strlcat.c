/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:36:59 by dkaiser           #+#    #+#             */
/*   Updated: 2024/03/10 13:15:10 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* size_t	ft_strlcat(char *dst, const char *src, size_t dstsize) */
/* { */
/* 	size_t	len; */
/* 	size_t	i; */

/* 	if (dstsize == 0) */
/* 		return (0); */
/* 	len = 0; */
/* 	while (len < dstsize - 1 && dst[len] != '\0') */
/* 	{ */
/* 		len++; */
/* 	} */
/* 	i = 0; */
/* 	while (len < dstsize - 1 && src[i] != '\0') */
/* 	{ */
/* 		dst[len] = src[i]; */
/* 		len++; */
/* 		i++; */
/* 	} */
/* 	dst[len] = '\0'; */
/* 	return (len); */
/* } */

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	dst_len;
	size_t	i;

	src_len = 0;
	while (src[src_len])
		src_len++;
	dst_len = 0;
	while (dst[dst_len])
		dst_len++;
	if (dst_len >= dstsize)
		return (dstsize + src_len);
	i = 0;
	while (i < src_len && dst_len + i < dstsize - 1)
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}

/* #include <stdio.h> */
/* int main () { */
/*     char dst[12] = "Hello "; */
/*     char dst2[12] = "Hello "; */
/*     char src[] = "World123"; */

/*     size_t len = strlcat(dst, src, 12); */
/*     size_t len2 = ft_strlcat(dst2, src, 12); */
/*     printf("strlcat (%zu): %s\n", len, dst); */
/*     printf("ft_strlcat (%zu): %s\n", len2, dst2); */
/* } */
