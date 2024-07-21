/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 02:49:43 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/21 22:37:26 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	sigint;

void	init_heredoc(t_info *info, t_command *cmd)
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

void	write_heredoc(char *delimiter, int fd)
{
	char	*input;

	while (TRUE)
	{
		write(1, "> ", 3);
		input = get_next_line(STDIN_FILENO);
		if (input == NULL || ft_strncmp(input, delimiter, ft_strlen(input)) == 0)
			break ;
		write(fd, input, ft_strlen(input));
		free(input);
	}
	if (input != NULL)
		free(input);
}

void	create_heredoc(t_info *info, t_command *cmd)
{
	int		fd;
	char	*delimiter;
	t_file	*f_lst;

	while (cmd != NULL && info->total_heredoc_cnt > 0)
	{
		f_lst = cmd->file_lst;
		while (f_lst != NULL && cmd->heredoc_cnt > 0)
		{
			if (f_lst->type == HEREDOC)
			{
				fd = open(f_lst->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
				delimiter = f_lst->delimit;
				write_heredoc(delimiter, fd);
				(cmd->heredoc_cnt)--;
				(info->total_heredoc_cnt)--;
				close(fd);
			}
			f_lst = f_lst->next;
		}
		cmd = cmd->next;
	}
	exit(SUCCESS);
}

void	handle_heredoc(int sig)
{
	if (sig == SIGINT)
		exit(FAIL);
}

int	process_heredoc(t_info *info, t_command *cmd)
{
	pid_t	pid;
	int		status;

	init_heredoc(info, cmd);
	pid = fork();
	if (!pid)
	{
		signal(SIGINT, handle_heredoc);
		create_heredoc(info, info->cmd);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
	}
	return (status);
}

void	delete_heredoc(t_command *cmd)
{
	t_file	*file;

	while (cmd != NULL)
	{
		file = cmd->file_lst;
		while (file != NULL)
		{
			if (file->type == HEREDOC)
			{
				if (access(file->file_name, F_OK) == 0)
					unlink(file->file_name);
				if (file->file_name != NULL)
				{
					free(file->file_name);
					file->file_name = NULL;
				}
			}
			file = file->next;
		}
		cmd = cmd->next;
	}
}
