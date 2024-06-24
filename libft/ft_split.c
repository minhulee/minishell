/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:58:46 by jewlee            #+#    #+#             */
/*   Updated: 2024/06/13 20:49:04 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	str_cnt(char const *s, char c)
{
	size_t	i;
	size_t	cnt;

	i = 0;
	cnt = 0;
	while (s[i] != '\0')
	{
		if ((i == 0 && s[i] != c) \
			|| (s[i] == c && s[i + 1] != c && s[i + 1] != '\0'))
			cnt++;
		i++;
	}
	return (cnt);
}

static char	*sub_dup(char const *s, size_t from, size_t str_len)
{
	char		*str;
	size_t		i;

	i = 0;
	str = (char *)malloc(sizeof(char) * (str_len + 1));
	if (str == NULL)
		return (NULL);
	while (i < str_len)
	{
		str[i] = s[from + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	**free_error(char **arr, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
	return (arr);
}

static char	**put_str(char **arr, char const *str, char c)
{
	size_t	i;
	size_t	j;
	size_t	from;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c && str[i] != '\0')
		{
			from = i;
			while (str[i] != c && str[i] != '\0')
				i++;
			arr[j] = sub_dup(str, from, (i - from));
			if (arr[j] == NULL)
				return (free_error(arr, j));
			if (j < str_cnt(str, c))
				j++;
		}
		i++;
		if (i > ft_strlen(str))
			break ;
	}
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char		**arr;
	size_t		cnt;

	if (s == NULL)
		return (NULL);
	cnt = str_cnt(s, c);
	arr = (char **)malloc(sizeof(char *) * (cnt + 1));
	if (arr == NULL)
		return (NULL);
	arr = put_str(arr, s, c);
	if (arr == NULL)
		return (NULL);
	arr[cnt] = NULL;
	return (arr);
}
