/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 12:27:12 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/30 11:14:28 by jewlee           ###   ########.fr       */
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
		if (access(find, F_OK) == 0)
		{
			if (is_dir(find) == TRUE)
			{
				free(find);
				return (NULL);
			}
			return (find);
		}
		free(find);
	}
	return (NULL);
}

static t_bool	check_relative_path(char *cmd)
{
	if (ft_strchr(cmd, '/') != NULL)
		return (TRUE);
	return (FALSE);
}

static char	*find_cmd_path(char **path, char *cmd)
{
	char	*path_cmd;
	char	*find;

	if (cmd == NULL || ft_strlen(cmd) == 0)
		return (NULL);
	if (!path || check_relative_path(cmd) == TRUE)
		return (ft_strdup(cmd));
	path_cmd = ft_strjoin("/", cmd);
	if (path_cmd == NULL)
		exit(FAIL);
	find = get_cmd_path(path, path_cmd);
	free(path_cmd);
	return (find);
}

void	get_path(char **path, t_command **cmd)
{
	t_command	*tmp;

	tmp = *cmd;
	while (tmp != NULL)
	{
		tmp->cmd_path = find_cmd_path(path, tmp->cmd); // -> PATH 환경변수에서 찾아보고
		tmp = tmp->next;
	}
}



// 1. 패스를 토대로 해당 파일이 있는지 확인한다.
// 2. 만약 패스에 없다면 현재 디렉토리를 기준으로 확인한다.
// 3. 1 -> 해당 파일이 없다면 -> command not found
// 4. 해당 파일이 존재하고 권한이 없다면 -> permissin denied | (execve)command not found
// 5. 해당 파일이 존재하고 권한이 있으면 라인 한줄 한줄을 입력으로 받아서 순차적으로 실행해준다...

// 6. 패스가 없다? -> 외부 함수 목록이 존재하지 않으므로 현재 디렉토리를 기준으로 찾는다.
// 7. 패스가 없고 해당 디렉토리에 없다 -> is a directory
// 8. 패스가 없고 해당 디렉토리에 파일이 있는데 권한이 없다 -> permission denied 
// 5. 해당 파일이 존재하고 권한이 있으면 라인 한줄 한줄을 입력으로 받아서 순차적으로 실행해준다...

// 패스가 존재하고 해당 패스에 없다 -> command not found
// 패스가 존재하고 해당 패스에 있다 -> permission denied | 해당 파일이 쉘 스크립트거나 주소가 아니면 command not found
// 패스가 없고 해당 디렉토리에 없다. -> is a directory
// 패스가 없고 해당 디렉토리에 있다. -> permission denied | 해당 파일이 쉘 스크립트거나 주소가 아니면 command not found
