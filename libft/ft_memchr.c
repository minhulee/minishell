/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 21:29:03 by jewlee            #+#    #+#             */
/*   Updated: 2024/06/09 16:36:46 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	while (n > 0)
	{
		if (*(unsigned char *)s == (unsigned char)c)
			return ((void *)s);
		s++;
		n--;
	}
	return (NULL);
}
/*
memchr - locate byte in byte string

#include <string.h>
void	*memchr(const void *s, int c, size_t n);

Description : The memchr func locates the first occurrence
of c(converted to an unsigned char)
in string s.

Return : The memchr func returns a pointer to the byte located,
or NULL if no such byte exists within n bytes.
*/