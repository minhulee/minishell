/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_unset.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:47:58 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/22 14:42:23 by jewlee           ###   ########.fr       */
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

static t_bool	unset_is_valid_name(char *s, t_info *info)
{
	if (!(*s == '_' || ft_isalpha(*s)))
	{
		info->exit_status = FAIL;
		ft_fprintf(STDERR_FILENO,
			"minishell: unset: `%s': not a valid identifier\n", s);
		return (FALSE);
	}
	while (*s != '\0')
	{
		if (!(*s == '_' || ft_isalnum(*s)))
		{
			info->exit_status = FAIL;
			ft_fprintf(STDERR_FILENO,
				"minishell: unset: `%s': not a valid identifier\n", s);
			return (FALSE);
		}
		s++;
	}
	return (TRUE);
}

static void	unset_env(char **args, t_list *env_lst, t_info *info, int *cnt)
{
	t_list	*tmp;
	char	*find;

	while (*(++args) != NULL)
	{
		if (unset_is_valid_name(*args, info) == FALSE)
			continue ;
		find = ft_strjoin(*args, "=");
		while (env_lst != NULL)
		{
			if (env_lst->next != NULL
				&& ft_strncmp(find, env_lst->next->content,
					ft_strlen(find)) == 0)
			{
				tmp = env_lst->next->next;
				ft_lstdelone(env_lst->next, free);
				env_lst->next = tmp;
				(*cnt)++;
				break ;
			}
			env_lst = env_lst->next;
		}
		free(find);
	}
}

void	builtins_unset(t_command *cmd, t_info *info)
{
	int		cnt;
	int		i;

	info->exit_status = SUCCESS;
	cnt = 0;
	unset_env(cmd->args, info->env_lst, info, &cnt);
	if (cnt > 0)
	{
		i = -1;
		while (info->dup_envp[++i] != NULL)
			free(info->dup_envp[i]);
		free(info->dup_envp);
		info->dup_envp = unset_dup_envp(info->env_lst);
		if (info->dup_envp == NULL)
			exit(FAIL);
	}
	if (cmd->is_parent != TRUE)
		exit(info->exit_status);
}
