/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:04:28 by jewlee            #+#    #+#             */
/*   Updated: 2024/08/01 17:08:47 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	wait_children(int ps_cnt, pid_t last_pid)
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

void	single_builtins(t_info *info)
{
	if (set_redirect_fd(info, info->cmd) == FAIL)
		return ;
	set_file_fd(info->cmd);
	info->cmd->is_parent = TRUE;
	ft_builtins(info->cmd, info);
}

static void	clear_path(char *path_env, char **split_path)
{
	int	i;

	if (path_env != NULL)
		free(path_env);
	if (split_path != NULL)
	{
		i = -1;
		while (split_path[++i] != NULL)
			free(split_path[i]);
		free(split_path);
	}
}

static void	run_cmd(t_info *info)
{
	char		**split_path;
	char		*path_env;
	int			ps_cnt;

	path_env = find_path(info->dup_envp);
	split_path = ft_split(path_env, ':');
	get_path(split_path, &(info->cmd));
	clear_path(path_env, split_path);
	ps_cnt = 0;
	run_commands(info, info->cmd, &ps_cnt);
	info->exit_status = wait_children(ps_cnt, info->pid);
}

t_status	ft_execute(t_info *info)
{
	if (!process_heredoc(info, info->cmd))
	{
		if (info->cmd->next == NULL && info->cmd->builtin_type != NOTBUILTIN)
			single_builtins(info);
		else if (info->cmd != NULL)
			run_cmd(info);
	}
	else
	{
		info->exit_status = FAIL;
		ft_fprintf(STDOUT_FILENO, "\n");
	}
	clear_executor(info);
	return (SUCCESS);
}
