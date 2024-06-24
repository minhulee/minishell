/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 12:25:18 by jewlee            #+#    #+#             */
/*   Updated: 2024/06/09 16:15:51 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	size;

	size = 0;
	while (lst != NULL)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

/*
ft_lstsize - calculate linked-list size

int	ft_lstsize(t_list *lst);

Description : The ft_lstsize func calculates linked-list size.
	Case 1) Empty linked-list.
	Case 2) Normal linked-list.

Return : linked-list size
*/