/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:56:53 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/20 00:55:01 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_signal(int sig)
{
	if (sig == SIGINT)// ctrl+c 새로운 프롬프트 출력
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay(); 
    }
}

void	init_signal(t_info *info)
{
	struct termios	term;

	term = info->og_term;
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
}

int	main(int argc, char **argv, char **envp)
{
	t_info		info;

	if (init_info(&info, envp) == FAIL)
		exit(FAIL);
	while (TRUE)
	{
		init_signal(&info);
		info.line = readline("minishell$ ");
		if (info.line == NULL)
		{
			ft_putstr_fd("\x1b[1A\033[11Cexit\n", STDOUT_FILENO);
			break ;
		}
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
