/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:32:35 by jewlee            #+#    #+#             */
/*   Updated: 2024/06/09 16:36:09 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst == NULL || del == NULL)
		return ;
	del(lst->content);
	free(lst);
	lst = 0;
}

/*
ft_lstdelone

void	ft_lstdelone(t_list *lst, void (*del)(void *));

Descript : Takes as a parameter an element and
frees the memory of the element’s content
using the func ’del’
given as a parameter and free the element.
The memory of ’next’ must not be freed.
*/