/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:56:53 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/02 15:06:37 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// envp -> 리스트로 .
int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_token		*token;
	t_command	*cmd;

	while (TRUE)
	{
		line = readline("minishell$ ");
		if (line == NULL)
		{
			printf("Input error\n");
			continue ;
		}
		add_history(line);
		token = ft_tokenize(line);
		if (token == NULL)
			continue ;
		cmd = ft_parse(token);
		if (cmd == NULL)
			continue ;
		ft_execute(cmd, envp);
		// cmd_lst_printf(cmd);
	}
	exit(SUCCESS);
}
