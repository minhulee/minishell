/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:04:28 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/12 15:07:14 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// pipex + redirect + heredoc.
// cmd 구조체 path 확인.
// cmd args 가 적절하지 않을 시 처리 필요.

int		wait_children(int ps_cnt, pid_t last_pid)
{
	int	exit_status;
	int	status;
	int	curr_pid;

	exit_status = 0;
	while (ps_cnt)
	{	
		curr_pid = waitpid(-1, &status, 0);
		if (curr_pid != -1)
			ps_cnt--;
		if (curr_pid == last_pid)
		{
			if (WIFEXITED(status))
				exit_status = WEXITSTATUS(status);
		}
	}
	return (exit_status);	
}

void	process_heredoc(t_info *info, t_command *cmd)
{
	
	while (info->total_heredoc_cnt != 0 || cmd != NULL)
	{
		if (cmd->heredoc_cnt != 0)
		{
			
			(cmd->heredoc_cnt)--;
			(info->total_heredoc_cnt)--;
		}
		cmd = cmd->next;
	}
}

t_status	ft_execute(t_info *info)
{
	char		**split_path;
	char		*path_env;
	int			exit_status;
	int			ps_cnt;

	process_heredoc(info, info->cmd);
	if (info->cmd->next == NULL && info->cmd->builtin_type != NOTBUILTIN)
		ft_builtins(info->cmd, info); // 단일 cmd + builtin
	else
	{
		path_env = find_path(info->dup_envp);
		split_path = ft_split(path_env, ':');
		get_path(split_path, &(info->cmd));
		ps_cnt = 0;
		run_commands(info, info->cmd, &ps_cnt);
		exit_status = wait_children(ps_cnt, info->pid);
	}
	return (SUCCESS);
}
