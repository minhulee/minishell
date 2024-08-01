/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 22:40:19 by jewlee            #+#    #+#             */
/*   Updated: 2024/08/01 19:49:40 by minhulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clear_executor(t_info *info)
{
	delete_heredoc(info->cmd);
	restore_std_fd(info->cmd);
	cmd_lst_clear(&(info->cmd));
}
