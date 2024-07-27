/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 02:43:40 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/25 18:12:02 by jewlee           ###   ########.fr       */
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

void	token_lst_printf(t_token *lst)
{
	while (lst != NULL)
	{
		printf("%d\n", lst->type);
		printf("%s\n", lst->value);
		lst = lst->next;
	}
}
