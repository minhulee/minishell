/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_export_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 00:01:57 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/22 14:06:48 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	change_env(char *arg, t_list *env_lst, char *ptr)
{
	while (env_lst != NULL)
	{
		if (ft_strncmp(arg, env_lst->content, ptr - arg + 1) == 0) // 존재한다면
		{
			free(env_lst->content);
			env_lst->content = ft_strdup(arg);
			if (env_lst->content == NULL) // 널가드 필요
				return (1);
		}
		env_lst = env_lst->next;
	}
	return (0);
}

void	export_fprintf_err(t_command *cmd, char *s, t_info *info)
{
	ft_fprintf(STDERR_FILENO,
			"minishell: export: %s: not a valid identifier\n", s);
	if (cmd->is_parent != TRUE)
		exit(FAIL);
	info->exit_status = FAIL;
}
