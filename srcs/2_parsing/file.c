/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 23:57:50 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/22 18:27:10 by minhulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// ft_strdup 널가드
t_file	*new_file(t_token_type type, char *content)
{
	t_file	*new;

	if (content == NULL)
		return (NULL);
	new = ft_calloc(1, sizeof(t_file));
	if (new == NULL)
		return (NULL);
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

void	file_lst_clear(t_file **lst)
{
	t_file	*curr;
	t_file	*tmp;

	if (lst == NULL)
		return ;
	curr = *lst;
	while (curr != NULL)
	{
		if (curr->file_name != NULL)
			free(curr->file_name);
		if (curr->delimit != NULL)
			free(curr->delimit);
		tmp = curr->next;
		free(curr);
		curr = tmp;
	}
	*lst = NULL;
}
