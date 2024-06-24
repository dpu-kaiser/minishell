/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:15:33 by dkaiser           #+#    #+#             */
/*   Updated: 2024/03/10 14:02:07 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	copy_str(char *dst, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	char	*result;

	len = ft_strlen(s1) + ft_strlen(s2);
	result = malloc(len + 1);
	if (result)
	{
		result[len] = '\0';
		len = copy_str(result, s1);
		len = copy_str(result + len, s2);
		return (result);
	}
	else
		return (0);
}

/* #include <stdio.h> */

/* int	main(void) */
/* { */
/* 	char	s1[] = "Hello "; */
/* 	char	s2[] = "World"; */

/* 	printf("%s\n", ft_strjoin(s1, s2)); */
/* } */
