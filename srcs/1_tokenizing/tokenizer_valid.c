/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_valid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 14:00:11 by jewlee            #+#    #+#             */
/*   Updated: 2024/06/26 22:51:21 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// 기존에 "hello'" 이걸 못받았는데 수정함.
t_bool	valid_quotes(char *line)
{
	char	tmp;

	while (*line != '\0')
	{
		if (*line == '\'' || *line == '\"')
		{
			tmp = *line;
			line++;
			line = ft_strchr(line, tmp);
			if (line == NULL)
				return (FALSE);
		}
		line++;
	}
	return (TRUE);
}
