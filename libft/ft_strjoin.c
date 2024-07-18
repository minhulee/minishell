/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:40:07 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/17 23:46:18 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	*ft_strcpy(char	*dst, char const *src)
{
	size_t	i;

	i = 0;
	while (src[i] != 0)
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}

static char	*dup_str(char const *s1, char const *s2)
{
	char	*ret;

	if (s2 == NULL)
		ret = ft_strdup(s1);
	else
		ret = ft_strdup(s2);
	return (ret);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;
	char	*new_str;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL || s2 == NULL)
		return (dup_str(s1, s2));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	new_str = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (new_str == NULL)
		return (NULL);
	new_str = ft_strcpy(new_str, s1);
	i = s1_len;
	while (s2_len != 0)
	{
		new_str[i] = *s2;
		s2++;
		i++;
		s2_len--;
	}
	new_str[i] = '\0';
	return (new_str);
}
/*
#include <stdio.h>

int	main(void)
{
	char	s1[] = "Hello ";
	char	s2[] = "World!";

	printf("%s\n", ft_strjoin(s1, s2));
}
*/