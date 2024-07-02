/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:04:28 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/02 15:03:27 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// pipex + redirect + heredoc.
// cmd 구조체 path 확인.
t_status	ft_execute(t_command *cmd, char **envp)
{
	char		**split_path;
	char		*path_env;

	// path 찾기
	path_env = find_path(envp);
	// : 로 분리
	split_path = ft_split(path_env, ':');
	// 각 cmd_path
	if (get_path(split_path, &cmd) == FAIL)
		return (FAIL);
	run_commands(cmd, envp);
	return (SUCCESS);
}
