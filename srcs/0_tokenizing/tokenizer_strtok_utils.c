/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_strtok_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 12:13:46 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/12 12:45:51 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*tokenize_quote_str(char **line)
{
	char	*tmp;
	char	*ptr;
	char	*value;

	tmp = *line;
	ptr = ft_strchr(*line + 1, *tmp);
	value = ft_substr(tmp, 1, (size_t)(ptr - tmp - 1));
	if (value == NULL)
		return (NULL);
	*line += (ptr - tmp + 1);
	return (value);
}

char	*tokenize_str(char **line)
{
	char	*tmp;
	char	*value;

	tmp = *line;
	while (**line != '\0')
	{
		if (ft_isspace(**line) == TRUE || ft_isquote(**line) == TRUE
			|| ft_isoperator(**line) == TRUE)
			break ;
		(*line)++;
	}
	value = ft_substr(tmp, 0, *line - tmp);
	if (value == NULL)
		return (NULL);
	return (value);
}
