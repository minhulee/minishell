/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:51:18 by minhulee          #+#    #+#             */
/*   Updated: 2024/08/02 11:01:16 by minhulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		g_sig = SIGINT;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
}

void	handle_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_sig = SIGINT;
		exit(1);
	}
	else if (sig == SIGQUIT)
	{
		g_sig = SIGQUIT;
		exit(0);
	}
}

void	restore_term(t_info *info)
{
	struct termios	term;

	term = info->og_term;
	term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	init_signal(t_info *info)
{
	struct termios	term;

	term = info->og_term;
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	if (g_sig == SIGINT)
		g_sig = SUCCESS;
}
