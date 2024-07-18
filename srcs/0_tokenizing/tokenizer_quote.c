/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 02:25:02 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/18 02:29:33 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*tokenize_strtok_chr(char **line, int c)
{
	char	*tmp;
	char	*ptr;
	char	*value;

	tmp = *line;
	ptr = ft_strchr(*line + 1, c);
	value = ft_substr(tmp, 1, (size_t)(ptr - tmp - 1));
	if (value == NULL)
		exit(FAIL);
	if (c == '$')// $ 여기로 옮겨야함.
		*line += (ptr - tmp);
	else if (c == '\'' || c == '"')
		*line += (ptr - tmp + 1);
	return (value);
}

// $abcd -> 없어도 환경변수 체크를 해야한다.
// "qk $ qlqdh" | "$"-> $ 그자체로
// "$abcd qskdhqkljdh"
// 변수 이름에는 영문, 숫자, _만 올수있음.
static char	*tokenize_strtok_env(char **line, char **envp)
{
	int		size;
	char	*var_name;
	char	*var_value;

	(*line)++;
	size = 0;
	while ((*line)[size] != '\0'
		&& (ft_isalnum((*line)[size]) || (*line)[size] == '_'))
		size++;
	if (size == 0)
	{
		var_value = ft_strdup("$");
		if (var_value == NULL)
			exit(FAIL);
		return (var_value);
	}
	var_name = ft_calloc(size + 1, sizeof(char));
	if (var_name == NULL)
		exit(FAIL);
	var_name = ft_strncpy(var_name, (*line), size);
	var_value = get_env_value(var_name, envp);
	free(var_name);
	(*line) += (size + 1);
	return (var_value);
}

static char	*tokenize_double_quote(char **line, char **envp)
{
	char	*quote_ptr;
	char	*dollar_ptr;
	char	*value;
	char	*env_value;

	quote_ptr = ft_strchr(*line + 1, '"');
	dollar_ptr = ft_strchr(*line, '$');
	if (dollar_ptr == NULL || dollar_ptr > quote_ptr)// $ 없거나 " " $ 일떄
		value = tokenize_strtok_chr(line, '"');
	else
	{
		(*line)++;
		value = NULL;
		env_value = NULL;
		while (*line < quote_ptr)
		{
			if (**line == '$')
				env_value = tokenize_strtok_env(line, envp);
			else
			{
				dollar_ptr = ft_strchr(*line, '$');
				if (dollar_ptr != NULL && dollar_ptr < quote_ptr)
					value = tokenize_strtok_chr(line, '$');
				else
					value = tokenize_strtok_chr(line, '"');
			}
			value = ft_strjoin(value, env_value);
			if (env_value != NULL)
				free(env_value);
		}
	}
	return (value);
}

char	*tokenize_quote(char **line, char **envp)
{
	char	*value;

	if (**line == '\'')
		value = tokenize_strtok_chr(line, '\'');
	else
		value = tokenize_double_quote(line, envp);
	return (value);
}
