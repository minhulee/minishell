/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 02:27:51 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/18 03:05:44 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*expand_variable(char **str, char **envp)
{
	int		size;
	char	*var_name;
	char	*var_value;

	size = 0;
	while ((*str)[size] != '\0' && (*str)[size] != '$')
		size++;
	var_name = ft_calloc(size + 1, sizeof(char));
	if (var_name == NULL)
		exit(FAIL);
	var_name = ft_strncpy(var_name, *str, size);
	var_value = get_env_value(var_name, envp);
	free(var_name);
	*str += size;
	return (var_value);
}

static char	*extract_string(char **str)
{
	char	*dollar_ptr;
	char	*value;
	int		size;

	dollar_ptr = ft_strchr(*str, '$');
	if (dollar_ptr == NULL || *(dollar_ptr + 1) == '\0')
	{
		value = ft_strdup(*str);
		if (value == NULL)
			exit(FAIL);
		*str = ft_strchr(*str, '\0');
		return (value);
	}
	size = dollar_ptr - *str;
	value = ft_calloc(size + 1, sizeof(char));
	if (value == NULL)
		exit(FAIL);
	value = ft_strncpy(value, *str, size);
	*str += size;
	return (value);
}

static char	*expand_string(char *str, char **envp)
{
	char	*after;
	char	*var_value;
	char	*before;

	before = str;
	after = NULL;
	var_value = NULL;
	while (*before != '\0')
	{
		if (*(before) == '$' && *(before + 1) != '\0')
		{
			before++;
			var_value = expand_variable(&before, envp);
		}
		else
			after = extract_string(&(before));
		after = ft_strjoin(after, var_value);
		free(var_value);
	}
	free(str);
	return (after);
}

// export a="ls "
// $a-l -> ls -l -> 여기서 토큰화 진행해야함.
char	*tokenize_str(char **line, char **envp)
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
		exit(FAIL);
	if (ft_strchr(value, '$') != NULL)
		value = expand_string(value, envp);// "ls -l" -> 근데 여기서 다시 잘라서 따로 토큰화 진행해야함.
	return (value);
}
