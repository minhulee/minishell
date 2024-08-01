/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 23:57:50 by jewlee            #+#    #+#             */
/*   Updated: 2024/08/01 19:48:36 by minhulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_file	*new_file(t_token_type type, char *content)
{
	t_file	*new;

	if (content == NULL)
		return (NULL);
	new = ft_calloc(1, sizeof(t_file));
	if (new == NULL)
		exit(FAIL);
	new->type = type;
	if (type == HEREDOC)
		new->delimit = super_join(content, ft_strdup("\n"));
	else
		new->file_name = content;
	return (new);
}

void	file_lst_append(t_file **f_lst, t_file *new)
{
	t_file	*curr;

	if (*f_lst == NULL)
	{
		*f_lst = new;
		return ;
	}
	curr = *f_lst;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = new;
}

void	file_lst_clear(t_file **f_lst)
{
	t_file		*cur;
	t_file		*next;

	if (*f_lst == NULL)
		return ;
	cur = *f_lst;
	while (cur != NULL)
	{
		sfree(cur->file_name);
		sfree(cur->delimit);
		next = cur->next;
		sfree(cur);
		cur = next;
	}
	*f_lst = NULL;
}
