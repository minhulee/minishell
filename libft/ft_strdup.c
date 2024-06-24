/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 22:15:32 by jewlee            #+#    #+#             */
/*   Updated: 2023/10/12 14:07:54 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	s_len;
	size_t	i;
	char	*ptr;

	s_len = 0;
	while (s[s_len] != 0)
		s_len++;
	ptr = (char *)malloc(sizeof(char) * (s_len + 1));
	if (ptr == 0)
		return (0);
	i = 0;
	while (i < s_len)
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
/*
#include <stdio.h>

int	main(void)
{
	char	*str;

	str = ft_strdup("Hello World!!");

	printf("%s\n", str);
}
*/