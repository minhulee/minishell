/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 00:00:51 by jewlee            #+#    #+#             */
/*   Updated: 2024/08/02 10:16:55 by minhulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	is_dir(char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (FALSE);
	return ((path_stat.st_mode & S_IFMT) == S_IFDIR);
}

static t_bool	valid_prev_path(char *path)
{
	char	*tmp_path;
	int		ptr;
	t_bool	first_slash;

	first_slash = FALSE;
	ptr = -1;
	while (path[++ptr] != '\0')
	{
		if (path[ptr] == '/')
		{
			if (!first_slash)
				first_slash = TRUE;
			else
			{
				tmp_path = ft_substr(path, 0, ptr);
				if (!is_dir(tmp_path) && ft_strchr(path + ptr, '/'))
				{
					free(tmp_path);
					return (FALSE);
				}
				free(tmp_path);
			}
		}
	}
	return (TRUE);
}

int	valid_redirects_in(t_command *cmd, char *path)
{
	if (valid_prev_path(path) == FALSE)
	{
		ft_fprintf(STDERR_FILENO,
			"minishell: %s: Not a directory\n", path);
		if (!cmd->is_parent)
			exit(FAIL);
		return (FAIL);
	}
	if (access(path, F_OK) == -1)
	{
		ft_fprintf(STDERR_FILENO,
			"minishell: %s: No such file or directory\n", path);
		if (!cmd->is_parent)
			exit(FAIL);
		return (FAIL);
	}
	if (access(path, R_OK) == -1)
	{
		ft_fprintf(STDERR_FILENO,
			"minishell: %s: Permission denied\n", path);
		if (!cmd->is_parent)
			exit(FAIL);
		return (FAIL);
	}
	return (SUCCESS);
}

int	valid_redirects_out(t_command *cmd, char *path)
{
	if (valid_prev_path(path) == FALSE)
	{
		ft_fprintf(STDERR_FILENO,
			"minishell: %s: Not a directory\n", path);
		if (!cmd->is_parent)
			exit(FAIL);
		return (FAIL);
	}
	if (is_dir(path))
	{
		ft_fprintf(STDERR_FILENO,
			"minishell: %s: is a directory\n", path);
		if (!cmd->is_parent)
			exit(FAIL);
		return (FAIL);
	}
	if (!access(path, F_OK) && access(path, W_OK) == -1)
	{
		ft_fprintf(STDERR_FILENO,
			"minishell: %s: Permission denied\n", path);
		if (!cmd->is_parent)
			exit(FAIL);
		return (FAIL);
	}
	return (SUCCESS);
}

void	valid_cmd_path(char *cmd_path)
{
	if (valid_prev_path(cmd_path) == FALSE)
	{
		ft_fprintf(STDERR_FILENO,
			"minishell: %s: Not a directory\n", cmd_path);
		exit(126);
	}
	if (access(cmd_path, F_OK) == -1)
	{
		ft_fprintf(STDERR_FILENO,
			"minishell: %s: No such file or directory\n", cmd_path);
		exit(127);
	}
	if (is_dir(cmd_path))
	{
		ft_fprintf(STDERR_FILENO,
			"minishell: %s: is a directory\n", cmd_path);
		exit(126);
	}
	if (!(!access(cmd_path, X_OK) && !access(cmd_path, R_OK)))
	{
		ft_fprintf(STDERR_FILENO,
			"minishell: %s: Permission denied\n", cmd_path);
		exit(126);
	}
}
