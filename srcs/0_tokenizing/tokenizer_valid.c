/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_valid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 14:00:11 by jewlee            #+#    #+#             */
/*   Updated: 2024/06/22 15:01:13 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	valid_quotes(char *line)
{
	t_stack	*st;
	t_bool	flag;

	st = NULL;
	while (*line != '\0')
	{
		if (*line == '\'' || *line == '\"')
		{
			if (st_is_empty(st) || st->quote != *line)
            	st_push(&st, *line);
            else
            	st_pop(&st);
		}
		line++;
	}
	flag = st_is_empty(st);
	while (st_is_empty(st) == FALSE)
		st_pop(&st);
	return (flag);
}
