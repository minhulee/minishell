/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:04:28 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/20 17:56:36 by jewlee           ###   ########.fr       */
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
		exit(1);
}

void	make_heredoc_file(t_info *info, t_command *cmd)
{
	int		i;
	char	*tmp_i;
	char	*tmp;
	t_file	*f_lst;

	i = 1;
	while (cmd != NULL)
	{
		f_lst = cmd->file_lst;
		while (f_lst != NULL)
		{
			if (f_lst->type == HEREDOC)
			{
				tmp_i = ft_itoa(i);
				tmp = ft_strjoin(TEMPFILE, tmp_i);
				free(tmp_i);
				f_lst->file_name = tmp;
			}
			f_lst = f_lst->next;
		}
		i++;
		cmd = cmd->next;
	}
}

t_status	ft_execute(t_info *info)
{
	char		**split_path;
	char		*path_env;
	int			exit_status;
	int			ps_cnt;
	pid_t	pid;
	int		status;

	make_heredoc_file(info, info->cmd);
	pid = fork();
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
