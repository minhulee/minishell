/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:56:55 by jewlee            #+#    #+#             */
/*   Updated: 2023/10/12 17:20:28 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	unsigned int	s_len;
	char			*aft_str;

	if (s == 0)
		return (0);
	s_len = (unsigned int)ft_strlen(s);
	aft_str = (char *)malloc(sizeof(char) * (s_len + 1));
	if (aft_str == 0)
		return (0);
	i = 0;
	while (i < s_len)
	{
		aft_str[i] = (*f)(i, s[i]);
		i++;
	}
	aft_str[i] = '\0';
	return (aft_str);
}
