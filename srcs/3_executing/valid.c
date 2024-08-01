/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 00:00:51 by jewlee            #+#    #+#             */
/*   Updated: 2024/08/01 17:01:28 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	is_dir(char *path)
{
	DIR	*dir;

	dir = opendir(path);
	if (dir)
	{
		closedir(dir);
		return (TRUE);
	}
	return (FALSE);
}

int	valid_redirects_path(char *path)
{
	if (is_dir(path))
	{
		ft_fprintf(STDERR_FILENO,
			"minishell: %s: is a directory\n", path);
		return (FAIL);
	}
	if (access(path, F_OK) == -1)
	{
		ft_fprintf(STDERR_FILENO,
			"minishell: %s: No such file or directory\n", path);
		return (FAIL);
	}
	if (access(path, X_OK) == -1)
	{
		ft_fprintf(STDERR_FILENO,
			"minishell: %s: Permission denied\n", path);
		return (FAIL);
	}
	return (SUCCESS);
}

void	valid_cmd_path(char *cmd_path)
{
	if (is_dir(cmd_path))
	{
		ft_fprintf(STDERR_FILENO,
			"minishell: %s: is a directory\n", cmd_path);
		exit(126);
	}
	if (access(cmd_path, F_OK) == -1)
	{
		ft_fprintf(STDERR_FILENO,
			"minishell: %s: No such file or directory\n", cmd_path);
		exit(127);
	}
	if (access(cmd_path, X_OK) == -1)
	{
		ft_fprintf(STDERR_FILENO,
			"minishell: %s: Permission denied\n", cmd_path);
		exit(126);
	}
}
