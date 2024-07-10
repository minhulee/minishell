/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 22:03:05 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/09 22:55:36 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// exit 3 | echo hello -> 다중 커맨드는 exit 이 안됨.
// exit 1 2 -> too many arguments.
// exit asej -> bash: exit: asdjhd: numeric argument required
void	builtins_exit(t_command *cmd)
{
	int	exit_value;

	printf("exit\n");
	if (cmd->args[1] == NULL)
		exit(SUCCESS);
	if (cmd->args[2] != NULL) // 부모와 자식 동작 다름.
	{ // 자식일 경우 exit 해야함.
		printf("minishell: exit: too many arguments\n");
		if (cmd->is_parent == TRUE)
			return ;
		else
			exit(FAIL);
	}
}
