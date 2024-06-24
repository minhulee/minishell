/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 19:45:02 by jewlee            #+#    #+#             */
/*   Updated: 2023/10/13 13:56:31 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i = 0;
	if (dst_len >= size)
		return (src_len + size);
	while (i + dst_len + 1 < size && src[i] != '\0')
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (src_len + dst_len);
}
/*
#include <string.h>
#include <stdio.h>

int	main(void)
{
	char	dst1[30] = "123";
	char	*src = "456789";

	size_t	ret1 = ft_strlcat(dst1, src, 7);
	printf("dest1 = %s\nreturn = %zu\n", dst1, ret1);
}
*/