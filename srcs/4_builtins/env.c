/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 21:20:46 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/27 15:16:47 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtins_env(t_info *info)
{
	int	i;

	info->exit_status = SUCCESS;
	i = -1;
	while (info->dup_envp[++i] != NULL)
	{
		if (ft_strchr(info->dup_envp[i], '=') != NULL)
			printf("%s\n", info->dup_envp[i]);
	}
}
