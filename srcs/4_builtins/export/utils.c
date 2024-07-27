/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 00:01:57 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/25 15:01:37 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	print_export(t_info *info)
{
	int		i;
	char	**envp;

	envp = info->dup_envp;
	i = -1;
	while (envp[++i] != NULL)
		printf("declare -x %s\n", envp[i]);
}

int	change_env(char *arg, t_list *env_lst, char *ptr)
{
	while (env_lst != NULL)
	{
		if (ft_strncmp(arg, env_lst->content, ptr - arg + 1) == 0)
		{
			free(env_lst->content);
			env_lst->content = ft_strdup(arg);
			if (env_lst->content == NULL)
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
