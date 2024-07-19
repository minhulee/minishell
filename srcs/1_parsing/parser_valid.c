/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_valid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 14:36:13 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/18 23:55:32 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	valid_operator_syntax(t_token *token)
{
	while (token != NULL)
	{
		if (token->type == PIPE)
		{
			if (token->prev == NULL || token->next == NULL
				|| (token->prev != NULL && token->prev->type == PIPE)
				|| (token->next != NULL && token->next->type == PIPE))
			{
				ft_fprintf(STDERR_FILENO, "minishell: Syntax error: pipe\n");
				return (FALSE);
			}
		}
		else if (ft_isredirect(token->type) == TRUE && ((token->next != NULL
					&& (ft_isredirect(token->next->type) == TRUE))
				|| token->next == NULL))
		{
			ft_fprintf(STDERR_FILENO, "minishell: syntax error: redirect\n");
			return (FALSE);
		}
		token = token->next;
	}
	return (TRUE);
}
