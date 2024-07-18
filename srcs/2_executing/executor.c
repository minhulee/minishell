/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:04:28 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/18 13:05:55 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

// heredoc 실행 완료 후 지우기.
t_status	ft_execute(t_info *info)
{
	char		**split_path;
	char		*path_env;
	int			exit_status;
	int			ps_cnt;

	process_heredoc(info, info->cmd);
	if (info->cmd->next == NULL && info->cmd->builtin_type != NOTBUILTIN)
	{
		set_redirect_fd(info->cmd);
		set_file_fd(info->cmd);
		ft_builtins(info->cmd, info);
	}
	else
	{
		path_env = find_path(info->dup_envp);
		split_path = ft_split(path_env, ':');
		get_path(split_path, &(info->cmd));
		ps_cnt = 0;
		run_commands(info, info->cmd, &ps_cnt);
		exit_status = wait_children(ps_cnt, info->pid);
	}
	delete_heredoc(info->cmd);
	file_lst_clear(&(info->cmd->file_lst));
	cmd_lst_clear(&(info->cmd));
	return (SUCCESS);
}
