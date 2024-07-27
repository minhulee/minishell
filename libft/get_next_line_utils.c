/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewoolee <jewoolee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 19:29:14 by jewoolee          #+#    #+#             */
/*   Updated: 2023/11/18 00:10:33 by jewoolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strnl(char *s)
{
	size_t	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

size_t	gnl_strlen(char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

char	*gnl_strdup(char *s)
{
	size_t	i;
	size_t	size;
	char	*dup_s;

	size = gnl_strlen(s);
	dup_s = (char *)malloc(sizeof(char) * (size + 1));
	if (dup_s == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		dup_s[i] = s[i];
		i++;
	}
	dup_s[i] = '\0';
	return (dup_s);
}

char	*gnl_strncpy(char *dst, char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*join_s;
	size_t	i;
	size_t	s1_len;
	size_t	s2_len;

	if (s1 == NULL)
		return (gnl_strdup(s2));
	s1_len = gnl_strlen(s1);
	s2_len = gnl_strlen(s2);
	join_s = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (join_s == NULL)
	{
		free(s1);
		return (NULL);
	}
	join_s = gnl_strncpy(join_s, s1, s1_len);
	free(s1);
	i = 0;
	while (i < s2_len)
	{
		join_s[s1_len + i] = s2[i];
		i++;
	}
	join_s[s1_len + i] = '\0';
	return (join_s);
}
