/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:24:11 by jewlee            #+#    #+#             */
/*   Updated: 2024/08/01 15:49:17 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_sig;

void	builtins_pwd(t_info *info)
{
	char	cwd[PATH_MAX];

	if (g_sig == SIGPIPE)
	{
		ft_fprintf(STDERR_FILENO, "minishell: pwd: write error: Broken pipe\n");
		ft_exit(info, FAIL);
	}
	info->exit_status = SUCCESS;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		printf("%s\n", info->pwd);
	else
		printf("%s\n", cwd);
}
