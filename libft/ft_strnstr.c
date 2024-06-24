/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 20:42:55 by jewlee            #+#    #+#             */
/*   Updated: 2023/10/13 14:29:19 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (i < n && haystack[0] != '\0')
	{
		if ((unsigned char)haystack[0] == (unsigned char)needle[0])
		{
			j = 0;
			while ((unsigned char)haystack[j] == (unsigned char)needle[j])
			{
				j++;
				if (i + j > n)
					return (0);
				if (needle[j] == '\0')
					return ((char *)haystack);
			}
		}
		haystack++;
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	str1[] = "Foo Bar Baz";
	char	str2[] = "Bar";

	printf("%s\n", strnstr(str1, str2, 11));
	printf("%s\n", ft_strnstr(str1, str2, 11));
	return (0);
}
*/