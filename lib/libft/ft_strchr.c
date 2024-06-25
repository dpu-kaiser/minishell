/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:12:39 by dkaiser           #+#    #+#             */
/*   Updated: 2024/03/10 13:15:56 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (!(char)c)
		return ((char *)&s[i]);
	return (0);
}

/* #include <stdio.h> */
/* #include <string.h> */

/* int	main(void) */
/* { */
/* 	char	str[] = "teste"; */

/* 	printf("strchr: %p\n", strchr(str, '\0')); */
/* 	printf("ft_strchr: %p\n", ft_strchr(str, '\0')); */
/* } */
