/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_set_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 17:30:15 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/18 02:53:17 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// 자식 기준 오른쪽 파이프만 있을경우(첫째) / 양쪽 / 왼쪽만
static void	set_pipe_fd(t_command *cmd)
{
	// 1. 단일 명령어 (no pipe)
	if (cmd->prev == NULL && cmd->next == NULL)
		return ;
	if (cmd->next != NULL)
	{// 오른쪽 파이프가 있으면.
		close(cmd->curr_pipe_fd[0]);
		dup2(cmd->curr_pipe_fd[1], STDOUT_FILENO);
		close(cmd->curr_pipe_fd[1]);
	}// 왼쪽 파이프가 있으면
	if (cmd->prev != NULL)
	{
		close(cmd->prev_pipe_fd[1]); // 출력 닫기
		dup2(cmd->prev_pipe_fd[0], STDIN_FILENO);
		close(cmd->prev_pipe_fd[0]);
	}
}

void	set_file_fd(t_command *cmd)
{
	if (cmd->infile_fd != NONE)
	{
		dup2(cmd->infile_fd, STDIN_FILENO);
		close(cmd->infile_fd);
	}
	if (cmd->outfile_fd != NONE)
	{
		dup2(cmd->outfile_fd, STDOUT_FILENO);
		close(cmd->outfile_fd);
	}
}

void	set_fd(t_command *cmd, t_info *info)
{
	set_pipe_fd(cmd);
	set_redirect_fd(cmd);
	set_file_fd(cmd);
}
