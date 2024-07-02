/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_f_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 23:57:50 by jewlee            #+#    #+#             */
/*   Updated: 2024/06/26 00:31:38 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_file	*file_lst_new(t_token_type type, char *name)
{
	t_file	*new;

	new = ft_calloc(1, sizeof(t_file));
	if (new == NULL)
		return (NULL);
	new->type = type;
	new->file_name = name;
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
		tmp = curr->next;
		free(curr);
		curr = tmp;
	}
	*lst = NULL;
}
