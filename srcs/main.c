/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:56:53 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/19 11:53:42 by jewlee           ###   ########.fr       */
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
		if (ft_strlen(info.line) == 0)
		{
			free(info.line);
			continue ;
		}
		add_history(info.line);
		info.token = ft_tokenize(info.line, info.dup_envp);
		if (info.token == NULL)
			continue ;
		info.cmd = ft_parse(info.token, &(info.total_heredoc_cnt));
		if (info.cmd == NULL)
			continue ;
		ft_execute(&info);
	}
	exit(SUCCESS);
}
