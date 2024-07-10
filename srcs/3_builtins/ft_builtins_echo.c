/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_echo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:41:02 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/10 15:08:56 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// echo a
static int	check_flag_n(t_command *cmd)
{
	int	i;
	int	j;

	i = 1;
	while (cmd->args[i])
	{
		if (cmd->args[i][0] != '-')
			return (i - 1);
		j = 1;
		while (cmd->args[i][j])
		{
			if (cmd->args[i][j] != 'n')
				return (i - 1);
			j++;
		}
		i++;
	}
	return (i);
}

// echo -nnnnnn hello 처리 필요함.
// echo -n -n -n -n hello 처리 필요함.
void	builtins_echo(t_command *cmd)
{
	int	i;

	if (cmd->args[1] == NULL)
	{
		printf("\n");
		return ;
	}
	i = check_flag_n(cmd);
	if (i > 0)
	{
		while (cmd->args[++i] != NULL)
		{
			printf("%s", cmd->args[i]);
			if (cmd->args[i + 1] != NULL)
				printf(" ");
		}
	}
	else
	{
		i = 0;
		while (cmd->args[++i] != NULL)
			printf("%s ", cmd->args[i]);
		printf("\n");
	}
}
