/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:19:35 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/25 15:26:08 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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

t_bool	env_is_existed(char	*arg, char **envp, char *ptr)
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

void	no_equal_char(char *s, t_info *info)
{
	if (!is_valid_name(s, s + ft_strlen(s)))
		export_fprintf_err(s, info);
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
				no_equal_char(cmd->args[i], info);
			else
			{
				if (cmd->args[i] < ptr)
					args_is_string(cmd, info, i, ptr);
				else
					export_fprintf_err(cmd->args[i], info);
			}
		}
	}
}
