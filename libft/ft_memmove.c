/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 13:06:59 by jewlee            #+#    #+#             */
/*   Updated: 2024/06/09 15:55:28 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (len == 0 || src == NULL || dst == NULL)
		return (dst);
	if (dst <= src)
		dst = ft_memcpy(dst, src, len);
	else
	{
		i = len - 1;
		while (i > 0)
		{
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
			i--;
		}
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
	}
	return (dst);
}

/*
memmove - copy byte string

#include <string.h>
void	*memmove(void *dst, const void *src, size_t len);

Description : The memmove func copies len bytes from string src to string dst.
The two strings may overlay; the copy is always done in a non-destructive manner.

Return : The memmove func returns the original value of dst.
*/