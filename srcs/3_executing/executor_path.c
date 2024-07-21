/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 12:27:12 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/21 23:42:53 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*find_path(char **envp)
{
	int		i;
	char	*ret_path;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
		{
			ret_path = ft_strdup(envp[i] + 5);
			if (ret_path == NULL)
				exit(FAIL);
			return (ret_path);
		}
		i++;
	}
	return (NULL);
}

static char	*get_cmd_path(char **path, char *path_cmd)
{
	int		i;
	char	*find;

	i = -1;
	while (path[++i] != NULL)
	{
		find = ft_strjoin(path[i], path_cmd);
		if (find == NULL)
			exit(FAIL);
		if (access(find, X_OK) == 0)
		{
			free(path_cmd);
			return (find);
		}
		free(find);
	}
	free(path_cmd);
	return (NULL);
}

static char	*find_cmd_path(char **path, char *cmd)
{
	int		i;
	char	*path_cmd;
	char	*find;

	if (cmd == NULL)
		return (NULL);
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	path_cmd = ft_strjoin("/", cmd);
	if (path_cmd == NULL)
		exit(FAIL);
	find = get_cmd_path(path, path_cmd);
	return (find);
}

void	get_path(char **path, t_command **cmd)
{
	t_command	*tmp;

	tmp = *cmd;
	while (tmp != NULL)
	{
		tmp->cmd_path = find_cmd_path(path, tmp->cmd);
		tmp = tmp->next;
	}
}
