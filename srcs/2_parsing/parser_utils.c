/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 21:09:48 by jewlee            #+#    #+#             */
/*   Updated: 2024/06/23 18:41:48 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cnt_pipe(t_token *token)
{
	int		cnt;

	cnt = 0;
	while (token != NULL)
	{
		if (token->type == PIPE)
			cnt++;
		token = token->next;
	}
	return (cnt);
}
