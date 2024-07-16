/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_run.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:49:29 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/16 11:24:56 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// > d cat
static void child_process(t_command *cmd, t_info *info)
{
	set_fd(cmd, info);
	if (cmd->cmd == NULL || cmd->cmd_path == NULL)
		exit(FAIL);
	if (cmd->cmd_path == NULL && cmd->cmd != NULL) // 적절한 명령어가 아닐때
	{
		err_printf(cmd->cmd);
		exit(FAIL);
	}
	else
	{
		if (cmd->builtin_type != NOTBUILTIN)
		{
			ft_builtins(cmd, info);
		}
		else if (execve(cmd->cmd_path, cmd->args, info->dup_envp) == -1)
		{
			perror("execve() error\n");
			exit(FAIL);
		}
		exit(SUCCESS);
	}
}

// 파이프 -> 포크 -> 자식 / 부모 행동.
// a | b | c | d
static void	parent_process(t_command *cmd)
{
	// prev_pipe_fd 는 첫번째 자식 이후를 위한 행동.
	if (cmd->next != NULL)
	{
		cmd->prev_pipe_fd[0] = cmd->curr_pipe_fd[0];
		cmd->prev_pipe_fd[1] = cmd->curr_pipe_fd[1];
		close(cmd->curr_pipe_fd[0]);
		close(cmd->curr_pipe_fd[1]);
	}
}

t_bool fork_error_catch(pid_t pid)
{
	if(pid == -1)
	{
		perror("fork() error\n");
		return (TRUE);
	}
	return (FALSE);
}

// qkhdsk | qkjsdhkqshd | builtins | 
void run_commands(t_info *info, t_command *cmd, int *cnt)
{
	while (cmd != NULL)
	{
		if (cmd->next != NULL) // 마지막 노드는 파이프 안만듬.
			pipe(cmd->curr_pipe_fd);
		info->pid = fork();
		if(fork_error_catch(info->pid))
			return ;
		else if (info->pid == 0)
			child_process(cmd, info);
		else
			parent_process(cmd);
		cmd = cmd->next;
		(*cnt)++;
	}
}
