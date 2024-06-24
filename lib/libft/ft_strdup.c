/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:54:16 by dkaiser           #+#    #+#             */
/*   Updated: 2024/03/10 15:28:58 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*result;
	int		len;

	len = ft_strlen(s1);
	result = malloc(len + 1);
	if (!result)
		return (0);
	result[len] = '\0';
	while (len--)
		result[len] = s1[len];
	return (result);
}

/* #include <stdio.h> */
/* int main() { */
/*     char *output; */
/*     char input[] = "test"; */
/*     output = ft_strdup(input); */
/*     printf("%s\n", output); */
/* } */
