/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_valid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 14:00:11 by jewlee            #+#    #+#             */
/*   Updated: 2024/06/26 23:00:00 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * 기존에 스택으로 따옴표 에러를 검사하는 로직에서
 * "hello'" 이런 경우를 에러로 처리했었음.
 * 에러 판단하는 로직을 수정함.
 */
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
