/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_f_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 23:57:50 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/16 12:08:10 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_file	*file_lst_new(t_token_type type, char *content)
{
	t_file	*new;

	if (content == NULL)
		return (NULL);// ft_strdup 널가드
	new = ft_calloc(1, sizeof(t_file));
	if (new == NULL)
		return (NULL);
	new->type = type;
	if (type == HEREDOC)
		new->delimit = content;
	else
		new->file_name = content;
	return (new);
}

void	file_lst_add_back(t_file **f_lst, t_file *new)
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
