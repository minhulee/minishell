/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:19:35 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/27 15:20:15 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*export_extract_name(char *env)
{
	char	*equal_ptr;
	char	*name;

	equal_ptr = ft_strchr(env, '=');
	if (equal_ptr != NULL)
		name = ft_substr(env, 0, equal_ptr - env);
	else
		name = ft_strdup(env);
	if (name == NULL)
		exit(FAIL);
	return (name);
}

void	change_env(char *arg, t_list *env_lst, char *arg_name)
{
	char	*env_name;

	while (env_lst != NULL)
	{
		env_name = export_extract_name(env_lst->content);
		if (!ft_strncmp(arg_name, env_name, ft_strlen(arg_name) + 1))
		{
			free(env_lst->content);
			env_lst->content = ft_strdup(arg);
			if (env_lst->content == NULL)
				exit(FAIL);
			free(env_name);
			return ;
		}
		free(env_name);
		env_lst = env_lst->next;
	}
}

static void	export_arg(t_command *cmd, t_info *info, int i)
{
	t_list	*new;
	char	*arg_name;

	arg_name = export_extract_name(cmd->args[i]);
	if (is_valid_name(arg_name) == TRUE)
	{
		if (declare_is_existed(arg_name, info->dup_envp) == FALSE)
		{
			new = ft_lstnew(ft_strdup(cmd->args[i]));
			ft_lstadd_back(&(info->env_lst), new);
		}
		else
			change_env(cmd->args[i], info->env_lst, arg_name);
		free(arg_name);
		info->dup_envp = unset_dup_envp(info->env_lst);
	}
	else
	{
		free(arg_name);
		export_fprintf_err(cmd->args[i], info);
	}
}

static void	declare_name(char *arg, t_info *info)
{
	t_list	*new;

	if (!is_valid_name(arg))
		export_fprintf_err(arg, info);
	else
	{
		if (declare_is_existed(arg, info->dup_envp) == TRUE)
			return ;
		else
		{
			new = ft_lstnew(ft_strdup(arg));
			ft_lstadd_back(&(info->env_lst), new);
			info->dup_envp = unset_dup_envp(info->env_lst);
		}
	}
}

void	builtins_export(t_command *cmd, t_info *info)
{
	int		i;
	char	*ptr;

	info->exit_status = SUCCESS;
	if (cmd->args[1] == NULL)
		print_export(info);
	else
	{
		i = 0;
		while (cmd->args[++i] != NULL)
		{
			ptr = ft_strchr(cmd->args[i], '=');
			if (ptr == NULL)
				declare_name(cmd->args[i], info);
			else
			{
				if (cmd->args[i] < ptr)
					export_arg(cmd, info, i);
				else
					export_fprintf_err(cmd->args[i], info);
			}
		}
	}
}
