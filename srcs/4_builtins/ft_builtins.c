/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:19:39 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/20 19:33:23 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// cd, env, pwd, echo 완료
void	ft_builtins(t_command *cmd, t_info *info)
{
	if (cmd->builtin_type == CD)
		builtins_cd(cmd);
	else if (cmd->builtin_type == ENV)
		builtins_env(info);
	else if (cmd->builtin_type == PWD)
		builtins_pwd(cmd);
	else if (cmd->builtin_type == ECHO_)
		builtins_echo(cmd);
	else if (cmd->builtin_type == EXIT)
		builtins_exit(cmd, info);
	else if (cmd->builtin_type == EXPORT)
		builtins_export(cmd, info);
	else if (cmd->builtin_type == UNSET)
		builtins_unset(cmd, info);
}
