/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 19:35:37 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/27 13:50:20 by minhulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	set_redirect_in(t_command *cmd, t_file *file)
{
	if (cmd->infile_fd != NONE)
		close(cmd->infile_fd);
	cmd->infile_fd = open(file->file_name, O_RDONLY, 0644);
	if (cmd->infile_fd < 0)
		valid_redirects_path(file->file_name);
}

static void	set_redirect_out(t_command *cmd, t_file *file)
{
	if (cmd->outfile_fd != NONE)
		close(cmd->outfile_fd);
	cmd->outfile_fd = open(file->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->outfile_fd < 0)
		valid_redirects_path(file->file_name);
}

static void	set_redirect_app_out(t_command *cmd, t_file *file)
{
	if (cmd->outfile_fd != NONE)
		close(cmd->outfile_fd);
	cmd->outfile_fd = open(file->file_name,
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (cmd->outfile_fd < 0)
		valid_redirects_path(file->file_name);
}

void	set_redirect_fd(t_command *cmd)
{
	t_file	*file;

	file = cmd->file_lst;
	while (file != NULL)
	{
		if (file->type == INPUT_REDIRECT || file->type == HEREDOC)
			set_redirect_in(cmd, file);
		else if (file->type == OUTPUT_REDIRECT)
			set_redirect_out(cmd, file);
		else if (file->type == APPEND_O_REDIRECT)
			set_redirect_app_out(cmd, file);
		file = file->next;
	}
}
