/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_strtok.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 22:13:48 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/18 12:43:28 by jewlee           ###   ########.fr       */
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

// a="ls "
// $a-al -> ls -al -> 성립.
static t_status	tokenize_identifier(char **line, t_token **token_lst, char **envp)
{
	t_token	*new;
	char	*tmp;
	char	*content;

	content = NULL;
	while (**line != '\0')
	{
		if (ft_isspace(**line) || ft_isoperator(**line))
			break ;
		if (**line == '"' || **line == '\'')
			tmp = tokenize_quote(line, envp);
		else
			tmp = tokenize_str(line, envp);
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
		exit(FAIL);
	token_lst_add_back(token_lst, new);
	return (SUCCESS);
}

t_token	*ft_strtok(char *line, char **envp)
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
		if (*line == '>' || *line == '<' || *line == '|')
			flag = tokenize_operator(&line, &token_lst);
		else
			flag = tokenize_identifier(&line, &token_lst, envp);
	}
	classify_identifier(token_lst);
	return (token_lst);
}
