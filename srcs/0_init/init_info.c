/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:07:36 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/20 00:06:33 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_status	init_info(t_info *info, char **envp)
{
	ft_memset(info, 0, sizeof(t_info));
	if (init_envp(info, envp) == FAIL)
		exit(FAIL);
	if (tcgetattr(STDIN_FILENO, &info->og_term) == -1)
		return (FAIL);
	return (SUCCESS);
}
