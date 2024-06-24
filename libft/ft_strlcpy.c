/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:43:03 by jewlee            #+#    #+#             */
/*   Updated: 2023/10/13 14:28:50 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	i;

	i = 0;
	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	while (i < src_len && i + 1 < size)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}
/*
#include <string.h>
#include <stdio.h>

int	main(void)
{
	char	*src = "123456";
	char	dest1[20];
	char	dest2[20];

	size_t	ret1 = strlcpy(dest1, src, 5);
	size_t	ret2 = ft_strlcpy(dest2, src, 5);
	printf("dest = %s\nreturn = %zu\n", dest1, ret1);
	printf("dest = %s\nreturn = %zu", dest2, ret2);
}
*/