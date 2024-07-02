/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_strtok.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 22:13:48 by jewlee            #+#    #+#             */
/*   Updated: 2024/06/26 22:52:02 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	char	*tmp;
	char	*value;
	t_token	*new;
	int		i;

	i = -1;
	tmp = *line;
	while (tmp[++i] != '\0')
	{
		if (ft_isspace(tmp[i]) == TRUE || ft_isquote(tmp[i]) == TRUE
			|| ft_isoperator(tmp[i]) == TRUE)
			break ;
	}
	value = ft_substr(tmp, 0, i);
	if (value == NULL)
		return (FAIL);
	new = token_lst_new(value, ARGUMENT);
	if (new == NULL)
	{
		free(value);
		return (FAIL);
	}
	token_lst_add_back(token_lst, new);
	(*line) += i;
	return (SUCCESS);
}

// "hello world"  -> 12
// hello world" -> 11
// "\"hello world\"" -> "hello world" 13 -> 11크기
// \"hello world\"\0 | -> 커서를 hello world 뒤로
static t_status	tokenize_quote(char **line, t_token **token_lst)
{
	int		i;
	char	*tmp;
	char	*ptr;
	char	*value;
	t_token	*new;

	tmp = *line;
	// seper = (*line)[0] -> ' || "
	ptr = ft_strchr(*line + 1, *tmp);
	value = ft_substr(tmp, 1, (size_t)(ptr - tmp - 1));
	if (value == NULL)
		return (FAIL);
	new = token_lst_new(value, ARGUMENT);
	if (new == NULL)
	{
		free(value);
		return (FAIL);
	}
	token_lst_add_back(token_lst, new);
	*line += (ptr - tmp + 1);
	return (SUCCESS);
}

// quotes error
// 1. split -> whitespace, 따옴표 안에, >, <, <<
t_token	*ft_strtok(char *line)
{
	t_status	flag;
	t_token		*token_lst;

	flag = SUCCESS;
	token_lst = NULL;
	while (*line != '\0')
	{
		if (flag == FAIL)
		{
			token_lst_clear(&token_lst);
			return (NULL);
		}
		while (ft_isspace(*line) == TRUE)
			line++;
		if (*line == '\0')
			break ;
		if (*line == '\'' || *line == '\"')
			flag = tokenize_quote(&line, &token_lst);
		else if (*line == '>' || *line == '<' || *line == '|')
			flag = tokenize_operator(&line, &token_lst);
		else
			flag = tokenize_identifier(&line, &token_lst);
	}
	classify_identifier(token_lst);
	return (token_lst);
}
