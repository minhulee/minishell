/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 22:15:39 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/21 23:34:10 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*is_exist_env(char *line, char**envp, int *ptr)
{
	char	*name;
	char	*res;
	int		i;

	res = NULL;
	i = 1;
	while (!(line[*ptr + i] == '\'' || line[*ptr + i] == '\"' || line[*ptr + i] == '$' || line[*ptr + i] == ' ') && line[*ptr + i])
		i++;
	name = ft_substr(line, *ptr + 1, i - 1);
	*ptr += i;
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
		return (ft_strdup(""));
	return (res);
}

void	sfree(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

char	*super_join(char *src1, char *src2)
{
	char	*dst;

	dst = ft_strjoin(src1, src2);
	sfree(src1);
	sfree(src2);
	return (dst);
}

char	*substitute_env(char *line, char **envp, int exit_status)
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
		if (line[ptr] == '\'' && !flag)
		{
			while (line[++ptr] != '\'') ;
			res = super_join(res, ft_substr(line, start, ++ptr));
			start = ptr;
		}
		else if (line[ptr] == '\"')
			flag = !flag;
		else if (line[ptr] == '$' && !ft_isoperator(line[ptr + 1]) && line[ptr + 1] != ' ' && line[ptr + 1] != '\0')
		{
			if (line[ptr + 1] == '?')
			{
				env = super_join(ft_substr(line, start, ptr - start), ft_itoa(exit_status));
				ptr += 2;
			}
			else
				env = super_join(ft_substr(line, start, ptr - start), is_exist_env(line, envp, &ptr));
			res = super_join(res, env);
			start = ptr;
			continue ;
		}
		ptr++;
	}
	 if (start != ptr)
	 	res = super_join(res, ft_substr(line, start, ptr - start));
	return (res);
}
