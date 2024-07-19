/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_unset.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:47:58 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/18 18:07:39 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**unset_dup_envp(t_list *env_lst)
{
	int		i;
	char	**ret;

	ret = ft_calloc(ft_lstsize(env_lst) + 1, sizeof(char *));
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (env_lst != NULL)
	{
		ret[i] = ft_strdup(env_lst->content);
		if (ret[i] == NULL)
		{
			while (--i >= 0)
			{
				free(ret[i]);
				free(ret);
				return (NULL);
			}
		}
		env_lst = env_lst->next;
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

static int	unset_env(char **args, t_list *env_lst)
{
	int		cnt;
	t_list	*tmp;
	char	*find;

	cnt = 0;
	while (*(++args) != NULL)
	{
		find = ft_strjoin(*args, "=");
		while (env_lst != NULL)
		{
			if (env_lst->next != NULL &&
				ft_strncmp(find, env_lst->next->content, ft_strlen(find)) == 0)
			{
				tmp = env_lst->next->next;
				ft_lstdelone(env_lst->next, free);
				env_lst->next = tmp;
				cnt++;
				break ;
			}
			env_lst = env_lst->next;
		}
		free(find);
	}
	return (cnt);
}

void	builtins_unset(t_command *cmd, t_info *info)
{
	int		cnt;
	int		i;

	cnt = unset_env(cmd->args, info->env_lst);
	if (cnt > 0)
	{
		i = -1;
		while (info->dup_envp[++i] != NULL)
			free(info->dup_envp[i]);
		free(info->dup_envp);
		info->dup_envp = unset_dup_envp(info->env_lst);
		if (info->dup_envp == NULL) // all free 필요.
			return ;
	}
	return ;
}
