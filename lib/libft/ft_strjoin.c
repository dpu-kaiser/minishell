/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:15:33 by dkaiser           #+#    #+#             */
/*   Updated: 2025/01/22 00:27:04 by chuhlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// static int	copy_str(char *dst, const char *src)
// {
// 	int	i;

// 	i = 0;
// 	while (src[i])
// 	{
// 		dst[i] = src[i];
// 		i++;
// 	}
// 	return (i);
// }

char *ft_strjoin(const char *s1, const char *s2)
{
    char *joined_str;
    size_t len1;
    size_t len2;

    if (!s1 || !s2)
        return (NULL);
    len1 = strlen(s1);
    len2 = strlen(s2);
    joined_str = malloc(len1 + len2 + 1);
    if (!joined_str)
        return (NULL);
    strcpy(joined_str, s1);
    strcat(joined_str, s2);
    return (joined_str);
}

/* #include <stdio.h> */

/* int	main(void) */
/* { */
/* 	char	s1[] = "Hello "; */
/* 	char	s2[] = "World"; */

/* 	printf("%s\n", ft_strjoin(s1, s2)); */
/* } */
