/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:24:11 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/25 18:54:13 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	global_sig;

void	builtins_pwd(t_info *info)
{
	char	cwd[PATH_MAX];

	if (global_sig == SIGPIPE)
	{
		// perror("bash: pwd: write error");
		ft_fprintf(STDERR_FILENO, " Broken pipe\n");
		ft_exit(info, SIGPIPE);
	}
	info->exit_status = SUCCESS;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd");
		info->exit_status = FAIL;
	}
	else
		printf("%s\n", cwd);
}
