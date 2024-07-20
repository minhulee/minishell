/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:04:28 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/20 17:18:41 by minhulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

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
			if (WIFEXITED(status))
				exit_status = WEXITSTATUS(status);
		}
	}
	return (exit_status);
}

void	handle_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		ft_fprintf(STDERR_FILENO, "exit\n");
		exit(1);
	}
}

t_status	ft_execute(t_info *info)
{
	char		**split_path;
	char		*path_env;
	int			exit_status;
	int			ps_cnt;

	pid_t	pid = fork();
	int		status;
	if (!pid)
	{
		signal(SIGINT, handle_heredoc);
		process_heredoc(info, info->cmd);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
	}
	if (status != 256)
	{
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
	}
	delete_heredoc(info->cmd);
	restore_std_fd(info->cmd);
	file_lst_clear(&(info->cmd->file_lst));
	cmd_lst_clear(&(info->cmd));
	return (SUCCESS);
}
