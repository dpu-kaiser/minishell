/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:36:44 by dkaiser           #+#    #+#             */
/*   Updated: 2024/05/08 11:49:32 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_word_count(char const *s, char c)
{
	int	word_count;
	int	cur_len;

	word_count = 0;
	cur_len = 0;
	while (*s)
	{
		if (!(*s) || *s == c)
		{
			cur_len = 0;
		}
		else
		{
			if (!cur_len)
				word_count++;
			cur_len++;
		}
		s++;
	}
	return (word_count);
}

static char	*get_next_token(char const **ptr_s, char c)
{
	int			i;
	int			len;
	char const	*s;
	char		*result;

	s = *ptr_s;
	while (*s && *s == c)
		s++;
	if (!*s)
		return (0);
	len = 0;
	while (s[len] && s[len] != c)
		len++;
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (0);
	i = 0;
	while (i < len)
		result[i++] = *(s++);
	result[i] = '\0';
	*ptr_s = s;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		word_count;
	int		w;

	word_count = get_word_count((char *)s, c);
	result = malloc(sizeof(char *) * (word_count + 1));
	if (!result)
		return (0);
	w = 0;
	while (w < word_count)
	{
		result[w] = get_next_token(&s, c);
		if (!result[w])
		{
			while (w--)
				free(result[w]);
			free(result);
			return (0);
		}
		w++;
	}
	result[w] = 0;
	return (result);
}

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

/* #include <stdio.h> */
/* int main() */
/* { */
/*     char s[] = "      split       this for   me  !"; */
/*     char **split = ft_split(s, ' '); */

/*     if (split) { */
/*         while(*split) { */
/*             printf("%s\n", *split); */
/*             split++; */
/*         } */
/*     } */
/* } */
