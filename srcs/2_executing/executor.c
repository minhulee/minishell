/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:04:28 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/16 00:07:33 by jewlee           ###   ########.fr       */
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

void	process_heredoc(t_info *info, t_command *cmd)
{
	int		fd;
	int		i;
	char	*tmp_i;
	char	*delimiter;
	char	*input;
	char	*tmp;
	t_file	*f_lst;

	i = 1;
	f_lst = cmd->file_lst;
	while (cmd != NULL && info->total_heredoc_cnt > 0)
	{
		while (f_lst != NULL && cmd->heredoc_cnt > 0)
		{
			if (f_lst->type == HEREDOC)
			{
				tmp_i = ft_itoa(i);
				tmp = ft_strjoin(TEMPFILE, tmp_i);
				free(tmp_i);
				fd = open(tmp, O_CREAT | O_WRONLY | O_TRUNC, 0600);
				delimiter = f_lst->delimit;
				while (TRUE)
				{
					write(1, "> ", 3);
					input = get_next_line(STDIN_FILENO);
					if (input == NULL || ft_strncmp(input, delimiter, ft_strlen(delimiter)) == 0)
						break ;
					write(fd, input, ft_strlen(input));
					free(input);
				}
				(cmd->heredoc_cnt)--;
				(info->total_heredoc_cnt)--;
				f_lst->file_name = ft_strdup(tmp);
				free(tmp);
				if (input != NULL)
					free(input);
				close(fd);
			}
			f_lst = f_lst->next;
		}
		i++;
		cmd = cmd->next;
	}
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
		ft_builtins(info->cmd, info);
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
