/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_echo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:41:02 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/21 23:04:47 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static void	print_args_with_flag(t_command *cmd)
{
	int	i;

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

void	builtins_echo(t_command *cmd, t_info *info)
{
	if (cmd->args[1] == NULL)
		printf("\n");
	else
		print_args_with_flag(cmd);
	info->exit_status = SUCCESS;
}
