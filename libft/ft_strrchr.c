/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 20:17:59 by jewlee            #+#    #+#             */
/*   Updated: 2023/10/13 13:58:16 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;

	i = 0;
	while (*s != 0)
	{
		s++;
		i++;
	}
	while (i >= 0)
	{
		if ((unsigned char)*s == (unsigned char)c)
			return ((char *)s);
		s--;
		i--;
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	str[] = "Hello World!";

	printf("%s\n", ft_strrchr(str, ' '));
}
*/