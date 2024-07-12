/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_run.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:49:29 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/12 12:55:41 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// > d cat
static void child_process(t_command *cmd, t_info *info)
{
	set_fd(cmd, info);
	if (cmd->cmd == NULL) // 명령어가 NULL 일때
		exit(SUCCESS);
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
			exit(SUCCESS);
		}
		else if (execve(cmd->cmd_path, cmd->args, info->dup_envp) == -1)
		{
			perror("execve() error\n");
			exit(FAIL);
		}
		exit(SUCCESS);
	}
	// 썻던 fd 닫아야함.
}

static void	parent_process(t_command *cmd, int *pipe_fd
	, int *prev_pipe_fd)
{
	if (cmd->next != NULL)
	{
		close(pipe_fd[1]);
		prev_pipe_fd[0] = pipe_fd[0];
		prev_pipe_fd[1] = pipe_fd[1];
	}
	else
	{
		if (prev_pipe_fd[0] != -1)
		{
			close(prev_pipe_fd[0]);
			close(prev_pipe_fd[1]);
		}
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
		if (cmd->next != NULL)
		{
			if (pipe(cmd->curr_pipe_fd) == -1)
				return (perror("pipe() error\n")); 
		}
		info->pid = fork();
		if(fork_error_catch(info->pid))
			return ;
		else if (info->pid == 0)
			child_process(cmd, info);
		else
			parent_process(cmd, cmd->curr_pipe_fd, cmd->prev_pipe_fd);
		cmd = cmd->next;
		(*cnt)++;
	}
}
