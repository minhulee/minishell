/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:56:53 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/31 09:44:49 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_sig;

void	handle_sigpipe(int sig)
{
	if (sig == SIGPIPE)
	{
		g_sig = SIGPIPE;
		ft_fprintf(STDERR_FILENO, " Broken pipe\n");
		exit(SIGPIPE);
	}
}

void	valid_out_pipe(t_info *info)
{
	signal(SIGPIPE, handle_sigpipe);
	if (g_sig != SIGPIPE)
		write(STDOUT_FILENO, "", 0);
	if (g_sig == SIGPIPE)
	{
		write(STDERR_FILENO, "minishell$ ", 11);
		info->line = get_next_line(STDIN_FILENO);
	}
	else
		info->line = readline("minishell$ ");
}

t_status	ft_minishell(t_info *info)
{
	info->token = ft_tokenize(info->line, info->dup_envp, info->exit_status);
	if (info->token == NULL)
		return (FAIL);
	info->cmd = ft_parse(info->token, &(info->total_heredoc_cnt));
	if (info->cmd == NULL)
		return (FAIL);
	ft_execute(info);
	return (SUCCESS);
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
		valid_out_pipe(&info);
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
