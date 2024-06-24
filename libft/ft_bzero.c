/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 17:45:25 by jewlee            #+#    #+#             */
/*   Updated: 2023/10/13 16:38:55 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = 0;
		i++;
	}
}
/*
#include <strings.h>
#include <stdio.h>

int	main(void)
{
	char	str[] = "Hello World";

	printf("%s\n", str);
	ft_bzero(str, 8);
	for (int i = 0; i < 12; i++)
		printf("%c", str[i]);
}
*/