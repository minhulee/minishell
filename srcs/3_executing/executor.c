/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:04:28 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/22 14:10:16 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int sigint;

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
			if (WIFSIGNALED(status) == TRUE)
				exit_status = 128 + WTERMSIG(status);
			else
				exit_status = WEXITSTATUS(status);
		}
	}
	if (exit_status == 130)
		ft_fprintf(STDERR_FILENO, "\n");
	if (exit_status == 131)
		ft_fprintf(STDERR_FILENO, "Quit: 3\n");
	return (exit_status);
}

t_status	ft_execute(t_info *info)
{
	char		**split_path;
	char		*path_env;
	int			exit_status;
	int			ps_cnt;
	int			status;

	if (info->total_heredoc_cnt > 0)
	{
		init_heredoc(info, info->cmd);
		status = process_heredoc(info, info->cmd);
	}
	if (status != 256)
	{
		if (info->cmd->next == NULL && info->cmd->builtin_type != NOTBUILTIN)
		{
			set_redirect_fd(info->cmd);
			set_file_fd(info->cmd);
			info->cmd->is_parent = TRUE;
			ft_builtins(info->cmd, info);
		}
		else
		{
			path_env = find_path(info->dup_envp);
			split_path = ft_split(path_env, ':');
			get_path(split_path, &(info->cmd));
			ps_cnt = 0;
			run_commands(info, info->cmd, &ps_cnt);
			info->exit_status = wait_children(ps_cnt, info->pid);
		}
	}
	clear_executor(info);
	return (SUCCESS);
}
