/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_strtok_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 12:13:46 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/18 02:28:17 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_value(char *name, char **envp)
{
	int		i;
	int		size;
	char	*equal_ptr;
	char	*find;
	char	*var_value;

	find = ft_strjoin(name, "=");
	var_value = NULL;
	i = -1;
	while (envp[++i] != NULL)
	{
		if (ft_strncmp(find, envp[i], ft_strlen(find)) == 0)
		{
			if (ft_strlen(envp[i]) == ft_strlen(find))// a= 진짜 없는거나
				return (ft_strdup(""));// 빈문자열 할당
			equal_ptr = ft_strchr(envp[i], '=');
			size = ft_strlen(++equal_ptr);
			var_value = ft_calloc(size + 1, sizeof(char));
			if (var_value == NULL)
				exit(FAIL);
			var_value = ft_strncpy(var_value, equal_ptr, size);
			break ;
		}
	}
	free(find);
	if (var_value == NULL)
		return (ft_strdup(""));
	return (var_value);
}
