/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:13:45 by jewlee            #+#    #+#             */
/*   Updated: 2024/06/09 16:26:16 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

/*
ft_lstlast - return the last element of the list

t_list	*ft_lstlast(t_list *lst);

Descript : The ft_lstlast func returns the last element of the list.
	Case 1) Empty list.
	Case 2) Normal list.

Return : The last element of the list.
*/