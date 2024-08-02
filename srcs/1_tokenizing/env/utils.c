/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 10:59:58 by minhulee          #+#    #+#             */
/*   Updated: 2024/08/02 09:27:11 by minhulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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

t_bool	subs_is_valid_name(char *name)
{
	int	i;

	if (name[0] != '_' && ft_isalpha(name[0]) != 1)
		return (FALSE);
	i = 1;
	while (name[i] != '\0')
	{
		if (ft_isalnum(name[i]) != 1 && name[i] != '_')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void	init_index(t_index *index)
{
	index->start = 0;
	index->ptr = 0;
	index->flag = FALSE;
}

char	*handle_single_quote(char *line, char *res, t_index *index)
{
	(index->ptr)++;
	while (line[index->ptr] != '\'')
		(index->ptr)++;
	(index->ptr)++;
	res = super_join(res, ft_substr(line, index->start,
				index->ptr - index->start));
	index->start = index->ptr;
	return (res);
}
