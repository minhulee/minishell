/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_set_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 17:30:15 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/06 13:43:11 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	set_pipe_fd(t_command *cmd)
{
	if (cmd->next != NULL) // 오른쪽 파이프
	{
		dup2(cmd->curr_pipe_fd[1], STDOUT_FILENO);
		close(cmd->curr_pipe_fd[1]);
		close(cmd->curr_pipe_fd[0]);
	}
	if (cmd->prev_pipe_fd[0] != -1) // 왼쪽 파이프
	{
		dup2(cmd->prev_pipe_fd[0], STDIN_FILENO);
		close(cmd->prev_pipe_fd[0]);
		close(cmd->prev_pipe_fd[1]);	
	}
}

void	set_fd(t_command *cmd, t_info *info)
{
	set_pipe_fd(cmd);
	set_redirect_fd(cmd);
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
