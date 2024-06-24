/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 13:42:00 by jewlee            #+#    #+#             */
/*   Updated: 2024/06/09 16:01:00 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (n > 0)
	{
		if (*((unsigned char *)s1) != *((unsigned char *)s2))
			return (*((unsigned char *)s1) - *((unsigned char *)s2));
		n--;
		s1++;
		s2++;
	}
	return (0);
}

/*
memcmp - compare byte string

#include <string.h>
int	memcmp(const void *s1, const void *s2, size_t n);

Description : The memcmp func compares byte string s1 
against byte string s2. Both strings are assumed to be n bytes long.

Return : The memcmp func returns 0 if the two strings are identical.
Otherwise returns the difference between the first two differing bytes.
Zero-length strings are always identical.
This behavior is not required by C and portable code should only depend
on the sign of the returned value.
*/