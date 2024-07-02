/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_run.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:49:29 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/02 15:00:35 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// heredoc 유의
// pipe시 포크떠서 cmd .
// 리다이렉션 왔을시, 표준 출력 파일 fd값으로 바꾸기.
void run_commands(t_command *cmd, char **envp)
{
	pid_t	pid;
	int		status;
	int		pipe_fd[2];
	int		prev_pipe_fd[2] = {-1, -1};

	while (cmd != NULL)
	{
		if (cmd->next != NULL)
		{
			if (pipe(pipe_fd) == -1)
			{
				printf("pipe() error\n");
			}
		}
		pid = fork();
		if (pid == -1)
		{
			printf("fork() error\n");
		}
		else if (pid == 0)
		{
			if (cmd->next != NULL) // 파이프가 있을 경우
			{
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(pipe_fd[0]);
			}
			if (prev_pipe_fd[0] != -1)
			{
				dup2(prev_pipe_fd[0], STDIN_FILENO);
				close(prev_pipe_fd[1]);
			}
			if (execve(cmd->cmd_path, cmd->args, envp) == -1)
			{
				printf("execve() error\n");
			}
		}
		else
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
		waitpid(pid, &status, 0);
		cmd = cmd->next;
	}
}
