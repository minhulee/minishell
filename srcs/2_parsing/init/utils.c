/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:22:27 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/25 15:59:43 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	increment_count_if_needed(int *cnt, t_token *token)
{
	if (token->type == COMMAND || token->type == ARGUMENT)
		(*cnt)++;
}

void	parsing_to_pipe_or_end(t_command **tmp, t_token **curr, int *cnt)
{
	if (init_arg(tmp, *curr, *cnt) == FAIL)
		exit(FAIL);
	*tmp = (*tmp)->next;
	*cnt = 0;
}
