/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:24:17 by dkaiser           #+#    #+#             */
/*   Updated: 2024/03/10 14:03:13 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in(char c, const char *str)
{
	while (*str)
	{
		if (c == *str)
			return (1);
		else
			str++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	char	*start;
	char	*end;
	char	*result;

	start = (char *)s1;
	while (is_in(*start, set))
		start++;
	i = ft_strlen(s1);
	end = (char *)s1 + i - 1;
	while (end > start && is_in(*end, set))
		end--;
	i = end - start + 1;
	result = malloc(i + 1);
	if (result)
	{
		result[i] = '\0';
		i = 0;
		while (start <= end)
			result[i++] = *(start++);
		return (result);
	}
	return (0);
}

/* #include <stdio.h> */

/* int	main(void) */
/* { */
/* 	char	s1[] = " \t   \t  \t  "; */

/* 	printf("%s\n", ft_strtrim(s1, " \t")); */
/* } */
