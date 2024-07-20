/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_cd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:39:49 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/20 17:57:20 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// 다시 구현바람.
void	builtins_cd(t_command *cmd)
{
	char	*new_dir;
	char	cwd[PATH_MAX];

	if (cmd->args[1] == NULL || (ft_strlen(cmd->args[1]) == 1 
		&& ft_strchr(cmd->args[1], '~') == cmd->args[1]))
	{
		chdir("/Users/"); // envp에서 USER_ZDOTDIR= 찾아서 오른쪽꺼 넣기.
		return ;
	}
	new_dir = cmd->args[1];
	// new_dir acess()로 해당 디렉토리가 있는지 -> 없는 디렉토리면 에러 띄워야댐
	chdir(new_dir);
	getcwd(cwd, sizeof(cwd));
	printf("%s\n", cwd);
}
