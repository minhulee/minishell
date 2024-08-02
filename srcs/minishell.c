/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:56:53 by jewlee            #+#    #+#             */
/*   Updated: 2024/08/02 10:45:17 by minhulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_sig;

t_status	ft_minishell(t_info *info)
{
	info->token = ft_tokenize(info->line, info->dup_envp, info->exit_status);
	if (info->token == NULL)
		return (FAIL);
	info->cmd = ft_parse(info->token, &(info->total_heredoc_cnt));
	if (info->cmd == NULL)
		return (FAIL);
	return (ft_execute(info));
}

int	main(int argc, char **argv, char **envp)
{
	t_info		info;

	(void)argc;
	(void)argv;
	if (init_info(&info, envp) == FAIL)
		exit(FAIL);
	while (TRUE)
	{
		init_signal(&info);
		info.line = readline("minishell$ ");
		if (info.line == NULL)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			break ;
		}
		if (ft_strlen(info.line) == 0)
		{
			free(info.line);
			continue ;
		}
		add_history(info.line);
		if (ft_minishell(&info) == FAIL)
			continue ;
	}
	exit(SUCCESS);
}
