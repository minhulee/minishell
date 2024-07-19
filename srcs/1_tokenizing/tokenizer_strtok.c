/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_strtok.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 22:13:48 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/18 19:29:54 by jewlee           ###   ########.fr       */
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

static t_status	tokenize_operator(char **line, t_token **token_lst)
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

static t_status	tokenize_identifier(char **line, t_token **token_lst)
{
	t_token	*new;
	char	*tmp;
	char	*content;

	content = NULL;
	while (**line != '\0' && !ft_isspace(**line) && !ft_isoperator(**line))
	{
		if (**line == '"' || **line == '\'')
			tmp = tokenize_quote_str(line);
		else
			tmp = tokenize_str(line);
		if (content != NULL)
		{
			content = ft_strjoin(content, tmp);
			free(tmp);
		}
		else
			content = tmp;
	}
	new = token_lst_new(content, ARGUMENT);
	if (new == NULL)
		return (FAIL);
	token_lst_add_back(token_lst, new);
	return (SUCCESS);
}

t_token	*ft_strtok(char *line)
{
	t_status	flag;
	t_token		*token_lst;

	flag = SUCCESS;
	token_lst = NULL;
	while (*line != '\0')
	{
		if (flag == FAIL)
			exit(FAIL);
		while (ft_isspace(*line) == TRUE)
			line++;
		if (*line == '\0')
			break ;
		if (*line == '>' || *line == '<' || *line == '|')
			flag = tokenize_operator(&line, &token_lst);
		else
			flag = tokenize_identifier(&line, &token_lst);
	}
	classify_identifier(token_lst);
	return (token_lst);
}
