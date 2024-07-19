/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 02:49:43 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/19 00:31:58 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	while (cmd != NULL && info->total_heredoc_cnt > 0)
	{
		f_lst = cmd->file_lst;
		while (f_lst != NULL && cmd->heredoc_cnt > 0)
		{
			if (f_lst->type == HEREDOC)
			{
				tmp_i = ft_itoa(i);
				tmp = ft_strjoin(TEMPFILE, tmp_i);
				free(tmp_i);
				fd = open(tmp, O_CREAT | O_WRONLY | O_TRUNC, 0644);
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
