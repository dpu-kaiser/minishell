/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 11:11:30 by dkaiser           #+#    #+#             */
/*   Updated: 2024/03/10 14:06:41 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*result;
	unsigned int	i;

	i = ft_strlen(s);
	result = malloc(sizeof(char) * (i + 1));
	if (!result)
		return (0);
	result[i] = '\0';
	i = 0;
	while (s[i])
	{
		result[i] = f(i, s[i]);
		i++;
	}
	return (result);
}

/* char func (unsigned int i, char c) */
/* { */
/*     c += i; */
/*     return (c); */
/* } */

/* #include <stdio.h> */
/* int main(){ */
/*     char str[] = "AAAAAAAA"; */
/*     printf("%s\n", ft_strmapi(str, func)); */
/* } */
