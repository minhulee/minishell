/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:41:21 by jewlee            #+#    #+#             */
/*   Updated: 2024/06/09 16:36:39 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*node;
	void	*tmp;

	if (lst == NULL || f == NULL || del == NULL)
		return (0);
	new_lst = NULL;
	while (lst != 0)
	{
		tmp = f(lst->content);
		node = ft_lstnew(tmp);
		if (node == NULL)
		{
			del(tmp);
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, node);
		lst = lst->next;
	}
	return (new_lst);
}

/*
ft_lstmap - iterate 'lst' and apply the function 'f'
to the content of each element.

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

Descript : Iterates the list ’lst’ and applies the func ’f’
to the content of each element.
Creates a new list resulting of the successive applications
of the func ’f’.
The ’del’ func is used to delete the content of an element if needed.

Return : A new list resulting of the successive applications of the func 'f'.
*/