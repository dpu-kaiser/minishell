/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:07:54 by dkaiser           #+#    #+#             */
/*   Updated: 2024/03/11 15:04:28 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	k;

	if (!*haystack && *needle)
		return (0);
	i = 0;
	if (*needle == '\0' || needle == haystack)
		return ((char *)haystack);
	while (i < len && haystack[i])
	{
		k = 0;
		while (haystack[i + k] && haystack[i + k] == needle[k] && i + k < len)
			k++;
		if (!needle[k])
			return ((char *)haystack + i);
		i++;
	}
	return (0);
}

/* #include <stdio.h> */

/* int	main(void) */
/* { */
/* 	char	haystack[] = "abc"; */
/* 	char	needle[] = "abcde"; */
/* 	size_t	len = 5; */

/* 	printf("strnstr: %s\n", strnstr(haystack, needle, len)); */
/* 	printf("ft_strnstr: %s\n", ft_strnstr(haystack, needle, len)); */
/* } */
