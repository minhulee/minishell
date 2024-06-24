/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:11:03 by jewlee            #+#    #+#             */
/*   Updated: 2023/10/12 16:58:52 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	*t_strcpy(char *dst, char const *src, size_t start, size_t dst_len)
{
	size_t	i;

	i = 0;
	while (i < dst_len)
	{
		dst[i] = src[start + i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		start;
	size_t		end;
	size_t		aft_strlen;
	char		*aft_str;

	if (s1 == 0 || set == 0)
		return (0);
	if (*set == '\0' && *s1 != '\0')
		return (ft_strdup(s1));
	start = 0;
	while (s1[start] != 0 && ft_strchr(set, s1[start]) != 0)
		start++;
	if (start == ft_strlen(s1))
		return (ft_strdup(""));
	end = (ft_strlen(s1) - 1);
	while (end != 0 && ft_strrchr(set, s1[end]) != 0)
		end--;
	aft_strlen = (end - start + 1);
	aft_str = (char *)malloc(sizeof(char) * (aft_strlen + 1));
	if (aft_str == 0)
		return (0);
	aft_str = t_strcpy(aft_str, s1, start, aft_strlen);
	return (aft_str);
}
