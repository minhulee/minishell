/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 14:00:11 by jewlee            #+#    #+#             */
/*   Updated: 2024/08/01 11:46:50 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
