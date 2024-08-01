/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 00:00:51 by jewlee            #+#    #+#             */
/*   Updated: 2024/08/01 19:04:48 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// t_bool	is_dir(char *path)
// {
// 	DIR	*dir;

// 	dir = opendir(path); // -> 폴더인가 아닌가? | 여는 권한이 없으면
// 	if (dir)
// 	{
// 		printf("1\n");
// 		closedir(dir);
// 		return (TRUE);
// 	}
// 	printf("0\n");
// 	return (FALSE);
// }

#include <sys/types.h>
#include <sys/stat.h>

t_bool	is_dir(char *path)
{
	struct stat path_stat;
    if (stat(path, &path_stat) != 0) {
        return FALSE;
    }
    return ((path_stat.st_mode & S_IFMT) == S_IFDIR);
}

void	valid_redirects_in(char *path)
{
	if (access(path, F_OK) == -1)
	{
		ft_fprintf(STDERR_FILENO,
			"minishell: %s: No such file or directory\n", path);
		exit(1);
	}
	if (access(path, R_OK) == -1)
	{
		ft_fprintf(STDERR_FILENO,
			"minishell: %s: Permission denied\n", path);
		exit(1);
	}
}

void	valid_redirects_out(char *path)
{
	if (is_dir(path))
	{
		ft_fprintf(STDERR_FILENO,
			"minishell: %s: is a directory\n", path);
		exit(1);
	}
	if (access(path, W_OK) == -1)
	{
		ft_fprintf(STDERR_FILENO,
			"minishell: %s: Permission denied\n", path);
		exit(1);
	}
}

void	valid_cmd_path(char *cmd_path)
{
	printf("%s\n", cmd_path);
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
