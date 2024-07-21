/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_cd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:39:49 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/21 23:21:27 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>
#include <sys/syslimits.h>
#include <unistd.h>

char	*load_home_dir(t_info *info, t_command *cmd, char *line)
{
	char	*home;

	if (!cmd->args[1])
	{
		// env 확인
		home = getenv("HOME");
		if (!home)
		{
			write(STDERR_FILENO, "cd : HOME not set\n", 21);
			return (NULL);
		}
		return (home);
	}
	return (ft_strjoin(info->home_dir, line));
}

void	ft_chdir(t_info *info, char *dir)
{
	char	cwd[PATH_MAX];
	char	*newpwd;
	char	*oldpwd;

	if (chdir(dir) != 0) // -> 있는 경로인지 확인
	{
		printf("%s: No such file or directory\n", dir);
		return ;
	}
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		if (info->pwd[ft_strlen(info->pwd) - 1] != '/')
			info->pwd = super_join(info->pwd, ft_strdup("/"));
		newpwd = ft_strjoin(info->pwd, dir);
	}
	else
		newpwd = ft_strdup(cwd);
	oldpwd = ft_strjoin("OLDPWD=", info->pwd);
	change_env(oldpwd, info->env_lst, oldpwd + 6);
	info->dup_envp = unset_dup_envp(info->env_lst);
	free(info->pwd);
	info->pwd = newpwd;
	chdir(newpwd);
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		ft_fprintf(STDERR_FILENO,
			"cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
}

void	builtins_cd(t_info *info, t_command *cmd)
{
	if (!cmd->args[1])
		ft_chdir(info, load_home_dir(info, cmd, NULL));
	else if (cmd->args[1][0] == '~')
		ft_chdir(info, load_home_dir(info, cmd, cmd->args[1] + 1));
	else
		ft_chdir(info, cmd->args[1]);
}
