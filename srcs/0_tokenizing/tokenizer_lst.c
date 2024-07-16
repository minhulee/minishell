/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 02:43:40 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/16 11:52:04 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*token_lst_new(char *value, t_token_type type)
{
	t_token	*new;

	new = (t_token *)ft_calloc(1, sizeof(t_token));
	if (new == NULL)
		return (NULL);
	new->value = value;
	new->type = type;
	return (new);
}

void	token_lst_add_back(t_token **lst, t_token *new)
{
	t_token	*curr;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	curr = *lst;
	while (curr->next != NULL)
		curr = curr->next;
	new->prev = curr;
	curr->next = new;
}

void	token_lst_clear(t_token **lst)
{
	t_token	*curr;
	t_token	*tmp;

	if (lst == NULL)
		return ;
	curr = *lst;
	while (curr)
	{
		if (curr->value != NULL)
			free(curr->value);
		tmp = curr->next;
		free(curr);
		curr = tmp;
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
