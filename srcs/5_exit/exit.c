/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:53:08 by minhulee          #+#    #+#             */
/*   Updated: 2024/07/25 18:51:44 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//void	ft_err(int exit_status)
//{

//}

void	ft_exit(t_info *info, int exit_status)
{
	info->exit_status = exit_status;
	exit(exit_status);
}