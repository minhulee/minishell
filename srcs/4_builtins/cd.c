/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:39:49 by jewlee            #+#    #+#             */
/*   Updated: 2024/08/01 16:09:15 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*load_home(t_list *env_lst)
{
	while (env_lst)
	{
		if (!ft_strncmp("HOME=", env_lst->content, 5))
			return (ft_strdup(getenv("HOME")));
		env_lst = env_lst->next;
	}
	return (NULL);
}

char	*load_dir(t_info *info, t_command *cmd)
{
	char	*home;

	if (!cmd->args[1])
	{
		home = load_home(info->env_lst);
		if (!home)
		{
			write(STDERR_FILENO, "cd : HOME not set\n", 19);
			info->exit_status = FAIL;
			return (NULL);
		}
		return (home);
	}
	else if (cmd->args[1][0] == '~')
		return (ft_strjoin(getenv ("HOME"), cmd->args[1] + 1));
	return (ft_strdup(cmd->args[1]));
}

void	chagne_oldpwd(t_info *info, char *newpwd)
{
	char	*oldpwd;

	oldpwd = ft_strjoin("OLDPWD=", info->pwd);
	change_env(oldpwd, info->env_lst, "OLDPWD");
	free_dup_envp(info);
	info->dup_envp = unset_dup_envp(info->env_lst);
	free(info->pwd);
	info->pwd = newpwd;
	free(oldpwd);
}

t_bool	ft_chdir(t_info *info, char *dir)
{
	char	cwd[PATH_MAX];
	char	*newpwd;

	if (chdir(dir) != 0)
	{
		ft_fprintf(STDERR_FILENO, "minishell: cd: %s: ", dir);
		return (FALSE);
	}
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		if (info->pwd[ft_strlen(info->pwd) - 1] != '/')
			info->pwd = super_join(info->pwd, ft_strdup("/"));
		newpwd = ft_strjoin(info->pwd, dir);
	}
	else
		newpwd = ft_strdup(cwd);
	chagne_oldpwd(info, newpwd);
	chdir(newpwd);
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		ft_fprintf(STDERR_FILENO, "cd: error retrieving current directory: ");
		ft_fprintf(STDERR_FILENO, "getcwd:cannot access parent directories: ");
		return (FALSE);
	}
	return (TRUE);
}

void	builtins_cd(t_info *info, t_command *cmd)
{
	char	*dir;

	info->exit_status = SUCCESS;
	dir = load_dir(info, cmd);
	if (!dir)
		return ;
	if (!ft_chdir(info, dir))
	{
		ft_fprintf(STDERR_FILENO, "No such file or directory\n");
		info->exit_status = FAIL;
	}
	sfree(dir);
}
