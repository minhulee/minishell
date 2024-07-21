/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_export.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:19:35 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/21 23:20:17 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_bool	is_valid_name(char *s, char *end)
{
	if (!(*s == '_' || ft_isalpha(*s)))
		return (FALSE);
	while (s < end)
	{
		if (!(*s == '_' || ft_isalnum(*s)))
			return (FALSE);
		s++;
	}
	return (TRUE);
}

static void	args_is_char(t_command *cmd, t_info *info, int i, char *ptr)
{
	if (*(ptr + 1) == '\0')
	{
		export_fprintf_err(cmd->args[i], info);
		if (ft_strchr(cmd->args[i + 1], '=') == NULL)
			export_fprintf_err(cmd->args[++i], info);
	}
	else
		export_fprintf_err(cmd->args[i], info);
}

static t_bool	env_is_existed(char	*arg, char **envp, char *ptr)
{
	int		i;

	i = -1;
	while (envp[++i] != NULL)
	{
		if (ft_strncmp(envp[i], arg, ptr - arg + 1) == 0)
			return (TRUE);
	}
	return (FALSE);
}

static void	args_is_string(t_command *cmd, t_info *info, int i, char *ptr)
{
	t_list	*new;

	if (is_valid_name(cmd->args[i], ptr))
	{
		if (*(ptr - 1) == '_' || *(ptr + 1) == '\0')
			return ;
		if (env_is_existed(cmd->args[i], info->dup_envp, ptr) == FALSE)
		{
			new = ft_lstnew(ft_strdup(cmd->args[i]));
			ft_lstadd_back(&(info->env_lst), new);
		}
		else
		{
			change_env(cmd->args[i], info->env_lst, ptr);
		}
		info->dup_envp = unset_dup_envp(info->env_lst);
	}
	else
		export_fprintf_err(cmd->args[i], info);
}

void	export_no_args(t_info *info)
{
	int		i;
	char	**envp;

	envp = info->dup_envp;
	i = -1;
	while (envp[++i] != NULL)
		printf("declare -x %s\n", envp[i]);
}

void	builtins_export(t_command *cmd, t_info *info)
{
	int		i;
	char	*ptr;

	info->exit_status = SUCCESS;
	if (cmd->args[1] == NULL)
		export_no_args(info);
	else
	{
		i = 0;
		while (cmd->args[++i] != NULL)
		{
			ptr = ft_strchr(cmd->args[i], '=');
			if (ptr == NULL)
				continue ;
			else
			{
				if (cmd->args[i] < ptr)
					args_is_string(cmd, info, i, ptr);
				else
					args_is_char(cmd, info, i, ptr);
			}
		}
	}
}
