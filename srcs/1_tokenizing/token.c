/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 02:43:40 by jewlee            #+#    #+#             */
/*   Updated: 2024/08/02 09:49:17 by minhulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*new_token(char *value, t_token_type type)
{
	t_token	*new;

	new = (t_token *)ft_calloc(1, sizeof(t_token));
	if (new == NULL)
		return (NULL);
	new->value = value;
	new->type = type;
	return (new);
}

void	token_lst_append(t_token **lst, t_token *new)
{
	t_token	*cur;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	cur = *lst;
	while (cur->next != NULL)
		cur = cur->next;
	new->prev = cur;
	cur->next = new;
}

void	token_lst_clear(t_token **lst)
{
	t_token	*cur;
	t_token	*next;

	if (lst == NULL)
		return ;
	cur = *lst;
	while (cur)
	{
		if (cur->value)
			sfree(cur->value);
		next = cur->next;
		sfree(cur);
		cur = next;
	}
	*lst = NULL;
}
