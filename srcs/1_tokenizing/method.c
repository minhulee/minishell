/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   method.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:47:00 by minhulee          #+#    #+#             */
/*   Updated: 2024/08/02 09:33:05 by minhulee         ###   ########seoul.kr  */
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
		exit(FAIL);
	*line += (ptr - tmp + 1);
	return (value);
}

char	*tokenize_str(char **line)
{
	char	*tmp;
	char	*value;

	tmp = *line;
	while (**line != '\0' && !ft_isspace(**line)
		&& !ft_isquote(**line) && !ft_isoperator(**line))
		(*line)++;
	value = ft_substr(tmp, 0, *line - tmp);
	if (value == NULL)
		exit(FAIL);
	return (value);
}

static t_status	append_operator(t_token_type type,
	char **line, t_token **token_lst)
{
	t_token	*new;

	new = new_token(NULL, type);
	if (new == NULL)
		return (FAIL);
	token_lst_append(token_lst, new);
	(*line)++;
	if (type == HEREDOC || type == APPEND_O_REDIRECT)
		(*line)++;
	return (SUCCESS);
}

t_status	tokenize_operator(char **line, t_token **token_lst)
{
	if (ft_strncmp(*line, "<<", 2) == 0)
		return (append_operator(HEREDOC, line, token_lst));
	else if (ft_strncmp(*line, ">>", 2) == 0)
		return (append_operator(APPEND_O_REDIRECT, line, token_lst));
	else if (ft_strncmp(*line, "<", 1) == 0)
		return (append_operator(INPUT_REDIRECT, line, token_lst));
	else if (ft_strncmp(*line, ">", 1) == 0)
		return (append_operator(OUTPUT_REDIRECT, line, token_lst));
	return (append_operator(PIPE, line, token_lst));
}

t_status	tokenize_identifier(char **line, t_token **token_lst)
{
	t_token	*new;
	char	*tmp;
	char	*content;

	content = NULL;
	while (**line != '\0' && !ft_isspace(**line) && !ft_isoperator(**line))
	{
		if (**line == '\"' || **line == '\'')
			tmp = tokenize_quote_str(line);
		else
			tmp = tokenize_str(line);
		content = super_join(content, tmp);
	}
	new = new_token(content, ARGUMENT);
	if (new == NULL)
		return (FAIL);
	token_lst_append(token_lst, new);
	return (SUCCESS);
}
