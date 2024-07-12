/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 15:05:14 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/12 14:11:04 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_builtin(t_command *cmd)
{
	while (cmd != NULL && cmd->cmd != NULL)
	{
		if (ft_strncmp(cmd->cmd, "cd", 3) == 0)
			cmd->builtin_type = CD;
		else if (ft_strncmp(cmd->cmd, "echo", 5) == 0)
			cmd->builtin_type = ECHO;
		else if (ft_strncmp(cmd->cmd, "export", 7) == 0)
			cmd->builtin_type = EXPORT;
		else if (ft_strncmp(cmd->cmd, "exit", 5) == 0)
			cmd->builtin_type = EXIT;
		else if (ft_strncmp(cmd->cmd, "unset", 6) == 0)
			cmd->builtin_type = UNSET;
		else if (ft_strncmp(cmd->cmd, "env", 4) == 0)
			cmd->builtin_type = ENV;
		else if (ft_strncmp(cmd->cmd, "pwd", 4) == 0)
			cmd->builtin_type = PWD;
		cmd = cmd->next;
	}
}
