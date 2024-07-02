/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_run.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:49:29 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/02 13:44:32 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// heredoc 유의
// pipe시 포크떠서 cmd .
// 리다이렉션 왔을시, 표준 출력 파일 fd값으로 바꾸기.
void run_commands(t_command *cmd, int cmd_cnt)
{
	int		pipefd[2];
	pid_t	pid;
	t_command *curr;

}
