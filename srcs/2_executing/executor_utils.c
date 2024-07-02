/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 12:36:08 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/02 12:37:49 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cmd_cnt(t_command *cmd)
{
	int	cnt;

	cnt = 0;
	while (cmd != NULL)
	{
		cnt++;
		cmd = cmd->next;
	}
	return (cnt);
}
