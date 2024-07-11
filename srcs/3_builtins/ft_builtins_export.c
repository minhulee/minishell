/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_export.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:19:35 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/11 16:29:08 by jewlee           ###   ########.fr       */
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

static void	args_is_char(t_command *cmd, int i, char *ptr)
{
	if (*(ptr + 1) == '\0')
	{
		printf("%s is invalid identifier\n", cmd->args[i]);
		if (ft_strchr(cmd->args[i + 1], '=') == NULL)
			printf("%s is invalid identifier\n", cmd->args[++i]);
	}
	else
		printf("%s is invalid identifier\n", cmd->args[i]);
}

static void	args_is_string(t_command *cmd, t_info *info, int i, char *ptr)
{
	t_list	*new;

	if (is_valid_name(cmd->args[i], ptr)) // is_valid_value 구현 필요.
	{
		if (*(ptr - 1) == '_' || *(ptr + 1) == '\0')
			return ;
		printf("%d\n", 1);
		// 리스트에 동일한 환경변수 확인절차 필요 -> 있으면 그 값 변경
		// 없으면 추가.
		new = ft_lstnew(ft_strdup(cmd->args[i]));
		ft_lstadd_back(&(info->env_lst), new);
		info->dup_envp = unset_dup_envp(info->env_lst);
	}
	else
		printf("%s is invalid identifier\n", cmd->args[i]);
}

// "_ b= 7"
void	builtins_export(t_command *cmd, t_info *info)
{
	int		i;
	char	*ptr;

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
				args_is_char(cmd, i, ptr);
		}
	}
}
