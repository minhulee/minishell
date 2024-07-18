/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:09:31 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/18 15:37:37 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	*sub_dup(char const *s, unsigned int start, size_t len)
{
	char			*aft_s;
	unsigned int	i;

	aft_s = (char *)malloc(sizeof(char) * (len + 1));
	if (aft_s == NULL)
		return (NULL);
	i = 0;
	while ((size_t)i < len)
	{
		aft_s[i] = s[start + i];
		i++;
	}
	aft_s[i] = '\0';
	return (aft_s);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_str;

	if (len == 0 || (size_t)start >= ft_strlen(s))
		return (ft_strdup(""));
	if ((size_t)start + len > ft_strlen(s))
	{
		sub_str = sub_dup(s, start, ft_strlen(s) - (size_t)start);
		if (sub_str == NULL)
			return (NULL);
	}
	else
	{
		sub_str = sub_dup(s, start, len);
		if (sub_str == NULL)
			return (NULL);
	}
	return (sub_str);
}
/*
#include <stdio.h>

int	main(void)
{
	char	str[] = "Hello World!";

	printf("%s\n", ft_substr(str, 6, 10));
}
*/