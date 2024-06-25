/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 21:58:31 by dkaiser           #+#    #+#             */
/*   Updated: 2024/03/10 15:39:38 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	slen;
	size_t			i;
	char			*result;

	slen = ft_strlen(s);
	if (start >= slen)
		len = 0;
	if (slen - start < len)
		len = (slen - start);
	result = malloc(len + 1);
	if (!result)
		return (0);
	result[len] = '\0';
	i = 0;
	while (i < len)
	{
		result[i] = s[i + start];
		i++;
	}
	return (result);
}

/* #include <stdio.h> */
/* int main () */
/* { */
/*     char s[] = "Hello there"; */
/*     char *substr = ft_substr(s, 0, 2); */
/*     printf("%s\n", substr); */
/* } */
