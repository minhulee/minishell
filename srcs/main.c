/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:56:53 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/12 13:12:54 by jewlee           ###   ########.fr       */
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
		info.cmd = ft_parse(info.token);
		if (info.cmd == NULL)
			continue ;
		// heredoc 을 infile로 치환한다.
		// 이때 각 heredoc은 파이프에 따라 구분된다. <- heredoc으로 입력된 입력이 pipe를 지원을 안해.
		// << a << b << c | << d << e << f
		// < tmp0 <tmp0 <tmp0 | <tmp1 <tmp1 <tmp1
		// ft_execute(&info);
		cmd_lst_printf(info.cmd);
		printf("heredoc_cnt = %d\n", info.here_doc_cnt);
	}
	exit(SUCCESS);
}
