/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 21:20:46 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/21 22:58:36 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtins_env(t_info *info)
{
	int	i;

	i = -1;
	while (info->dup_envp[++i] != NULL)
		printf("%s\n", info->dup_envp[i]);
	info->exit_status = SUCCESS;
}
