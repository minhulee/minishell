/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:24:11 by jewlee            #+#    #+#             */
/*   Updated: 2024/08/02 08:50:01 by minhulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtins_pwd(t_info *info)
{
	char	cwd[PATH_MAX];

	info->exit_status = SUCCESS;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		printf("%s\n", info->pwd);
	else
		printf("%s\n", cwd);
}
