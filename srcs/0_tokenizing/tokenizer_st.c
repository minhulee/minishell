/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_st.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:07:59 by jewlee            #+#    #+#             */
/*   Updated: 2024/06/19 15:56:18 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_stack *st_create_node(char quote)
{
	t_stack	*new;

	new = (t_stack *)malloc(sizeof(t_stack));
	if (new == NULL)
		return (NULL);
	new->quote = quote;
	new->next = NULL;
	return (new);
}

void	st_push(t_stack **stack, char quote)
{
    t_stack *new;

	new = st_create_node(quote);
    new->next = *stack;
    *stack = new;
}

char	st_pop(t_stack **stack)
{
    t_stack *top;
    char	quote;

    if (*stack == NULL)
        return ('\0');
	top = *stack;
	quote = top->quote;
    *stack = top->next;
    free(top);
    return (quote);
}

t_bool	st_is_empty(t_stack *stack)
{
	if (stack == NULL)
		return (TRUE);
    return (FALSE);
}
