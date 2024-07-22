/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_pwd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:24:11 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/22 14:02:22 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtins_pwd(t_command *cmd, t_info *info)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		ft_fprintf(STDERR_FILENO, "getcwd() error\n");
		exit(FAIL);
	}
	else
	{
		printf("%s\n", cwd);
		info->exit_status = SUCCESS;
	}
}
