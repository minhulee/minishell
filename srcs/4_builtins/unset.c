/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:47:58 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/31 09:43:08 by jewlee           ###   ########.fr       */
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
		ft_fprintf(STDERR_FILENO,
			"minishell: unset: `%s': not a valid identifier\n", s);
		info->exit_status = FAIL;
		return (FALSE);
	}
	while (*(++s) != '\0')
	{
		if (!(*s == '_' || ft_isalnum(*s)))
		{
			ft_fprintf(STDERR_FILENO,
				"minishell: unset: `%s': not a valid identifier\n", s);
			info->exit_status = FAIL;
			return (FALSE);
		}
	}
	return (TRUE);
}

static t_bool	unset_is_existed(char *arg, char *env)
{
	char	*env_name;

	env_name = export_extract_name(env);
	if (!ft_strncmp(arg, env_name, ft_strlen(arg) + 1))
	{
		free(env_name);
		return (TRUE);
	}
	free(env_name);
	return (FALSE);
}

static void	unset_env(char **args, t_list *env_lst, t_info *info, int *cnt)
{
	t_list	*tmp;

	while (*(++args) != NULL)
	{
		if (unset_is_valid_name(*args, info) == FALSE)
			continue ;
		while (env_lst != NULL)
		{
			if (env_lst->next != NULL
				&& unset_is_existed(*args, env_lst->next->content))
			{
				tmp = env_lst->next->next;
				ft_lstdelone(env_lst->next, free);
				env_lst->next = tmp;
				(*cnt)++;
				break ;
			}
			env_lst = env_lst->next;
		}
	}
}

void	builtins_unset(t_command *cmd, t_info *info)
{
	int		cnt;

	info->exit_status = SUCCESS;
	cnt = 0;
	unset_env(cmd->args, info->env_lst, info, &cnt);
	if (cnt > 0)
	{
		free_dup_envp(info);
		info->dup_envp = unset_dup_envp(info->env_lst);
		if (info->dup_envp == NULL)
			exit(FAIL);
	}
}
