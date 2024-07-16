/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:56:53 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/16 12:04:17 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_info		info;

	if (init_envp(&info, envp) == FAIL)
		exit(FAIL);
	while (TRUE)
	{
		info.line = readline("minishell$ ");
		if (info.line == NULL)
			exit(FAIL);
		add_history(info.line);
		info.token = ft_tokenize(info.line);
		if (info.token == NULL)
			continue ;
		info.cmd = ft_parse(info.token, &(info.total_heredoc_cnt));
		if (info.cmd == NULL)
			continue ;
		ft_execute(&info);
		// 진행 후 cmd와 f_lst할당 해제 필요.
	}
	exit(SUCCESS);
}
