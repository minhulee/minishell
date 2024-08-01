/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:51:18 by minhulee          #+#    #+#             */
/*   Updated: 2024/08/01 14:03:44 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
}

void	handle_sigpipe(int sig)
{
	if (sig == SIGPIPE)
	{
		g_sig = SIGPIPE;
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

void	init_signal(t_info *info)
{
	struct termios	term;

	term = info->og_term;
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	signal(SIGINT, handle_sigint);
	// signal(SIGPIPE, handle_sigpipe);
	signal(SIGQUIT, SIG_IGN);
}
