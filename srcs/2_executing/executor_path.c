/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 12:27:12 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/02 15:04:26 by jewlee           ###   ########.fr       */
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
			return (ret_path);
		}
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(char **path, char *cmd)
{
	int		i;
	char	*path_cmd;
	char	*tmp;

	if (access(cmd, X_OK) == 0)
		return (cmd);
	path_cmd = ft_strjoin("/", cmd);
	i = -1;
	while (path[++i] != NULL)
	{
		tmp = ft_strjoin(path[i], path_cmd);
		if (access(tmp, X_OK) == 0)
		{
			free(path_cmd);
			return (tmp);
		}
		free(tmp);
	}
	free(path_cmd);
	return (NULL);
}

t_status	get_path(char **path, t_command **cmd)
{
	t_command	*tmp;

	tmp = *cmd;
	while (tmp != NULL)
	{
		tmp->cmd_path = get_cmd_path(path, tmp->cmd);
		if (tmp->cmd_path == NULL)
		{
			printf("Command not found\n");
			return (FAIL);
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}
