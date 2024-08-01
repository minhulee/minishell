/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 19:35:37 by jewlee            #+#    #+#             */
/*   Updated: 2024/08/01 19:31:30 by minhulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	set_redirect_in(t_command *cmd, t_file *file)
{
	if (cmd->infile_fd != NONE)
		close(cmd->infile_fd);
	if (valid_redirects_in(cmd, file->file_name) == FAIL)
		return (FAIL);
	cmd->infile_fd = open(file->file_name, O_RDONLY, 0644);
	return (SUCCESS);
}

static int	set_redirect_out(t_command *cmd, t_file *file)
{
	if (cmd->outfile_fd != NONE)
		close(cmd->outfile_fd);
	if (valid_redirects_out(cmd, file->file_name) == FAIL)
		return (FAIL);
	cmd->outfile_fd = open(file->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (SUCCESS);
}

static int	set_redirect_app_out(t_command *cmd, t_file *file)
{
	if (cmd->outfile_fd != NONE)
		close(cmd->outfile_fd);
	if (valid_redirects_out(cmd, file->file_name) == FAIL)
		return (FAIL);
	cmd->outfile_fd = open(file->file_name,
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	return (SUCCESS);
}

int	set_redirect_fd(t_command *cmd)
{
	t_file	*file;
	int		res;

	file = cmd->file_lst;
	while (file != NULL)
	{
		if (file->type == INPUT_REDIRECT || file->type == HEREDOC)
			res = set_redirect_in(cmd, file);
		else if (file->type == OUTPUT_REDIRECT)
			res = set_redirect_out(cmd, file);
		else if (file->type == APPEND_O_REDIRECT)
			res = set_redirect_app_out(cmd, file);
		if (res == FAIL)
			return (FAIL);
		file = file->next;
	}
	return (SUCCESS);
}
