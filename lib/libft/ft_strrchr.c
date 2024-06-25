/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:25:30 by dkaiser           #+#    #+#             */
/*   Updated: 2024/03/10 12:51:38 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*last_occurrence;

	last_occurrence = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			last_occurrence = (char *)&s[i];
		i++;
	}
	if (!(char)c)
		last_occurrence = (char *)&s[i];
	return (last_occurrence);
}

/* #include <stdio.h> */
/* #include <string.h> */

/* int	main(void) */
/* { */
/* 	char	str[] = "Hello world"; */

/* 	printf("strrchr: %s\n", strrchr(str, 'o')); */
/* 	printf("ft_strrchr: %s\n", ft_strrchr(str, 'o')); */
/* } */
