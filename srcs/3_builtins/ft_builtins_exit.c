/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 22:03:05 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/18 18:37:02 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// exit 3 | echo hello -> 다중 커맨드는 exit 이 안됨.
// exit 1 2 -> too many arguments.
// exit asej -> bash: exit: asdjhd: numeric argument required
// 0 ~ 255 의 종료 코드를 가진다.
void	builtins_exit(t_command *cmd)
{
	int	exit_value;

	printf("exit\n");
	if (cmd->args[1] == NULL)
		exit(SUCCESS);
	if (cmd->args[2] != NULL)
	{
		printf("minishell: exit: too many arguments\n");
		if (cmd->is_parent == TRUE)
			return ;
		else
			exit(FAIL);
	}
}
