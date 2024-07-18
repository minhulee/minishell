/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:12:58 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/18 15:47:06 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// char	*tok_substr(char *line, int c)
// {
// 	char	*ptr;
// 	char	*result;
// 	int		size;
	
// 	ptr = ft_strchr((*line) + 1, c);
// 	size = ptr - (*line) + 1;
// 	result = ft_calloc(size + 1, sizeof(char));
// 	if (result == NULL)
// 		exit(FAIL);
// 	result = ft_strncpy(result, (*line), size);
// 	*line += size;
// 	return (result);
// }

// aaaa$a aaaa "$a " '$a ' "aa'$a' " 'aaa"$a"aaa'
// aaaab aaaa "b "   '$a ' ptr
// char	*substitute_env(char *line, char **envp)
// {
// 	int		ptr;
// 	char	*single_quote;
// 	char	*var_value;
// 	char	*value;

// 	ptr = 0;
// 	while (*line)
// 	{
// 		if (*line == '\'')
// 			single_quote = tok_substr(&line, '\'');
// 		else
// 		{
// 			if (*line == '$')
// 				var_value = 
// 			else if (!ft_strchr(*line, '$') && !ft_strchr(*line, '\''))
// 				value = tok_substr(&line, '\0');
// 		}
// 	}
// }

char	*is_exist_env(char *line, char**envp, int *ptr)
{
	char	*name;
	char	*res;
	int		i;

	printf("%d\n", *ptr);
	res = NULL;
	i = 0;
	while (line[*ptr + i] != '\'' && line[*ptr + i] != '\"' && line[*ptr + i])
		i++;
	*ptr += i;
	name = ft_substr(line, *ptr + 1, *ptr + i);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], name, ft_strlen(name)))
		{
			res = ft_substr(envp[i], ft_strlen(name) + 1, ft_strlen(envp[i]));
			break ;
		}
		i++;
	}
	free(name);
	if (!res)
		return ("");
	return (res);
}

void	sfree(void	*ptr)
{
	if (ptr)
		free(ptr);
}

char	*super_join(char *src1, char *src2)
{
	char	*dst;

	dst = ft_strjoin(src1, src2);
	sfree(src1);
	sfree(src2);
	return (dst);
}
// aaaa$a aaaa "$a " '$a ' "aa'$a' " 'aaa"$a"aaa'
// aaaab  aaaa "b 
char	*substitute_env2(char *line, char **envp)
{
	int		start;
	int		ptr;
	char	*res;
	char	*env;
	t_bool	flag;

	start = 0;
	ptr	= 0;
	flag = FALSE;
	res = NULL;
	while (line[ptr])
	{
		if (line[ptr] == '\'' && flag)
		{
			while (line[++ptr] == '\'')
			res = super_join(res, ft_substr(line, start, ptr));
		}
		else if (line[ptr] == '\"')
			flag = !flag;
		else if (line[ptr] == '$')
		{
			env = super_join(ft_substr(line, start, ptr), is_exist_env(line, envp, &ptr));
			res = super_join(res, env);
			printf("%d\n", ptr);
			start = ptr;
		}
		ptr++;
	}
	printf("%d | %d\n", start, ptr);
	// if (start != ptr)
	// 	res = superjoin(res, ft_substr(line, start, ptr));
	return (res);
}

t_token	*ft_tokenize(char *line, char **envp)
{
	t_token	*token_lst;
	char	*expand_line;

	if (valid_quotes(line) == FALSE)
	{
		printf("Quotes errors\n");
		return (NULL);
	}
	expand_line = substitute_env2(line, envp);
	printf("%s\n", expand_line);
	exit(0);
	// token_lst = ft_strtok(line, envp);
	// free(line);
	// return (token_lst);
}
