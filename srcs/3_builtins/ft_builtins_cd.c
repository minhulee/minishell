/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_cd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:39:49 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/06 21:11:36 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// 다시 구현바람.
void	builtins_cd(t_command *cmd)
{
	char	*new_dir;
	char	cwd[PATH_MAX];

	new_dir = cmd->args[1];
	chdir(new_dir);
	getcwd(cwd, sizeof(cwd));
	printf("%s\n", cwd);
}
