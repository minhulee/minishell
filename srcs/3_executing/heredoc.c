/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 02:49:43 by jewlee            #+#    #+#             */
/*   Updated: 2024/08/02 08:56:40 by minhulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_heredoc(t_command *cmd)
{
	int		i;
	char	*itoa;
	t_file	*f_lst;

	i = 1;
	while (cmd != NULL)
	{
		f_lst = cmd->file_lst;
		while (f_lst != NULL)
		{
			if (f_lst->type == HEREDOC)
			{
				itoa = ft_itoa(i);
				f_lst->file_name = ft_strjoin(TEMPFILE, itoa);
				free(itoa);
				if (!f_lst->file_name)
					exit(FAIL);
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
		if (input == NULL || ft_strncmp(input, delimiter,
				ft_strlen(input)) == 0)
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
	t_file	*f_lst;

	while (cmd != NULL && info->total_heredoc_cnt > 0)
	{
		f_lst = cmd->file_lst;
		while (f_lst != NULL && cmd->heredoc_cnt > 0)
		{
			if (f_lst->type == HEREDOC)
			{
				fd = open(f_lst->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
				write_heredoc(f_lst->delimit, fd);
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

int	process_heredoc(t_info *info, t_command *cmd)
{
	pid_t	pid;
	int		status;

	status = 0;
	if (info->total_heredoc_cnt <= 0)
		return (status);
	init_heredoc(cmd);
	pid = fork();
	if (!pid)
	{
		signal(SIGINT, handle_heredoc);
		signal(SIGQUIT, handle_heredoc);
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
			}
			file = file->next;
		}
		cmd = cmd->next;
	}
}
