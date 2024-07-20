/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_run.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:49:29 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/20 18:39:18 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void child_process(t_command *cmd, t_info *info)
{
	set_fd(cmd, info);
	if (cmd->cmd == NULL || cmd->cmd_path == NULL)
		exit(SUCCESS);
	if (cmd->cmd_path == NULL && cmd->cmd != NULL)
	{
		ft_fprintf(STDERR_FILENO,
				"minishell: %s: command not found\n", cmd->cmd);
		exit(FAIL);
	}
	else
	{
		if (cmd->builtin_type != NOTBUILTIN)
			ft_builtins(cmd, info);
		else if (execve(cmd->cmd_path, cmd->args, info->dup_envp) == -1)
		{
			ft_fprintf(STDERR_FILENO, "execve() error\n");
			exit(FAIL);
		}
		exit(SUCCESS);
	}
}

static void	parent_process(t_command *cmd)
{
	if (cmd->prev != NULL)
		close(cmd->prev_pipe_fd[0]);
	if (cmd->next != NULL)
	{
		cmd->next->prev_pipe_fd[0] = cmd->curr_pipe_fd[0];
		cmd->next->prev_pipe_fd[1] = cmd->curr_pipe_fd[1];
		close(cmd->curr_pipe_fd[1]);
	}
}

t_bool fork_error_catch(pid_t pid)
{
	if(pid == -1)
	{
		ft_fprintf(STDERR_FILENO, "fork() error\n");
		exit(FAIL);
	}
	return (FALSE);
}

void run_commands(t_info *info, t_command *cmd, int *cnt)
{
	while (cmd != NULL)
	{
		if (cmd->next != NULL)
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