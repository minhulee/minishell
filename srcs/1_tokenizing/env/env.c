/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 22:15:39 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/25 12:37:23 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*extract_name(char *line, t_index *idx)
{
	int		i;
	char	*name;

	i = 1;
	while (line[idx->ptr + i] && !(ft_isquote(line[idx->ptr + i])
			|| line[idx->ptr + i] == '$'
			|| ft_isspace(line[idx->ptr + i])
			|| ft_isoperator(line[idx->ptr + i])))
		i++;
	name = ft_substr(line, idx->ptr + 1, i - 1);
	idx->ptr += i;
	return (name);
}

char	*is_exist_env(char *line, char **envp, t_index *idx)
{
	char	*name;
	char	*res;
	int		i;

	res = NULL;
	name = extract_name(line, idx);
	if (subs_is_valid_name(name) == FALSE)
		return (super_join(ft_strdup("$"), name));
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], name, ft_strlen(name)))
		{
			res = ft_substr(envp[i], ft_strlen(name) + 1,
					ft_strlen(envp[i]) - ft_strlen(name) + 1);
			break ;
		}
		i++;
	}
	free(name);
	if (!res)
		return (ft_strdup(""));
	return (res);
}

char	*replace_exit_status(char *line, t_index *idx, int exit_status)
{
	char	*env;

	env = super_join(ft_substr(line, idx->start, idx->ptr - idx->start),
			ft_itoa(exit_status));
	idx->ptr += 2;
	return (env);
}

char	*handle_dollar(char *line, char *res, t_index *idx, t_token_info *info)
{
	char	*env;

	if (line[idx->ptr + 1] == '?')
		env = replace_exit_status(line, idx, info->exit_status);
	else
		env = super_join(ft_substr(line, idx->start, idx->ptr - idx->start),
				is_exist_env(line, info->envp, idx));
	res = super_join(res, env);
	idx->start = idx->ptr;
	return (res);
}

char	*substitute_env(char *line, t_token_info *info)
{
	t_index	idx;
	char	*res;

	init_index(&idx);
	res = NULL;
	while (line[idx.ptr] != '\0')
	{
		if (line[idx.ptr] == '\'' && !idx.flag)
		{
			res = handle_single_quote(line, res, &idx);
			continue ;
		}
		else if (line[idx.ptr] == '\"')
			idx.flag = !idx.flag;
		else if (line[idx.ptr] == '$')
		{
			res = handle_dollar(line, res, &idx, info);
			continue ;
		}
		(idx.ptr)++;
	}
	if (idx.start != idx.ptr)
		res = super_join(res, ft_substr(line, idx.start, idx.ptr - idx.start));
	return (res);
}
