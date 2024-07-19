/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_set_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 17:30:15 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/19 01:15:06 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	set_pipe_fd(t_command *cmd)
{
	if (cmd->prev == NULL && cmd->next == NULL)
		return ;
	if (cmd->next != NULL)
	{
		close(cmd->curr_pipe_fd[0]);
		dup2(cmd->curr_pipe_fd[1], STDOUT_FILENO);
		close(cmd->curr_pipe_fd[1]);
	}
	if (cmd->prev != NULL)
	{
		dup2(cmd->prev_pipe_fd[0], STDIN_FILENO);
		close(cmd->prev_pipe_fd[0]);
	}
}

void	set_file_fd(t_command *cmd)
{
	if (cmd->infile_fd != NONE)
	{
		cmd->saved_stdin = dup(STDIN_FILENO);
		dup2(cmd->infile_fd, STDIN_FILENO);
		close(cmd->infile_fd);
	}
	if (cmd->outfile_fd != NONE)
	{
		cmd->saved_stdout = dup(STDOUT_FILENO);
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

void	restore_std_fd(t_command *cmd)
{
	if (cmd->infile_fd != NONE)
	{
		dup2(cmd->saved_stdin, STDIN_FILENO);
		close(cmd->saved_stdin);
	}
	if (cmd->outfile_fd != NONE)
	{
		dup2(cmd->saved_stdout, STDOUT_FILENO);
		close(cmd->saved_stdout);
	}
}
