/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 21:55:28 by jewlee            #+#    #+#             */
/*   Updated: 2024/06/23 16:07:40 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	i;

	ptr = malloc(size * count);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < (size * count))
	{
		((unsigned char *)ptr)[i] = '\0';
		i++;
	}
	return (ptr);
}
/*
#include <stdio.h>

int	main(void)
{
	int	*arr;

	arr = (int *)ft_calloc(4, sizeof(int));

	for (int i = 0; i < 4; i++)
	{
		printf("arr = %-10d\n", arr[i]);
	}
	free(arr);
}
*/