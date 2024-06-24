/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:38:28 by jewlee            #+#    #+#             */
/*   Updated: 2024/06/09 16:35:48 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (lst == NULL || f == NULL)
		return ;
	while (lst != NULL)
	{
		f(lst->content);
		lst = lst->next;
	}
}

/*
ft_lstiter - Iterate the list ’lst’ and apply the func ’f’
to the content of each element.

void	ft_lstiter(t_list *lst, void (*f)(void *));

Descript : The ft_lstiter func iterates 'lst' and
apply 'f' to the content of each element.
	Exceptianl situation) lst == NULL or f == NULL
*/