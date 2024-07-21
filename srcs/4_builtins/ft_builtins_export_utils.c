/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_export_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 00:01:57 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/21 23:19:48 by jewlee           ###   ########.fr       */
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

void	export_fprintf_err(char *s, t_info *info)
{
	ft_fprintf(STDERR_FILENO,
			"minishell: export: %s: not a valid identifier\n", s);
	info->exit_status = FAIL;
}
