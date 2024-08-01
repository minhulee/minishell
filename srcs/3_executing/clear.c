/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 22:40:19 by jewlee            #+#    #+#             */
/*   Updated: 2024/08/01 15:01:13 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clear_executor(t_info *info)
{
	delete_heredoc(info->cmd);
	restore_std_fd(info->cmd);
	file_lst_clear(info->cmd);
	cmd_lst_clear(&(info->cmd));
}
