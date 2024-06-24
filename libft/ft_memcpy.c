/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 17:52:36 by jewlee            #+#    #+#             */
/*   Updated: 2024/06/09 16:34:53 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (dst == NULL && src == NULL)
		return (dst);
	i = 0;
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dst);
}

/*
memcpy - copy memory area

#include <string.h>
void	*memcpy(void *restrict dst, const void *restrict src, size_t n);

Description : The memcpy func copies n bytes
from memory area src to memory area dst.
If dst and src overlap, behavior is undefined.
Applications in which dst and src might
overlap should use memmove instead.

Return : The memcpy func returns the original value of dst.
*/