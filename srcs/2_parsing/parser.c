/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:55:49 by jewlee            #+#    #+#             */
/*   Updated: 2024/08/01 12:10:22 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	check_builtin(t_command *cmd)
{
	while (cmd != NULL && cmd->cmd != NULL)
	{
		if (ft_strncmp(cmd->cmd, "cd", 3) == 0)
			cmd->builtin_type = CD;
		else if (ft_strncmp(cmd->cmd, "echo", 5) == 0)
			cmd->builtin_type = ECHO_;
		else if (ft_strncmp(cmd->cmd, "export", 7) == 0)
			cmd->builtin_type = EXPORT;
		else if (ft_strncmp(cmd->cmd, "exit", 5) == 0)
			cmd->builtin_type = EXIT;
		else if (ft_strncmp(cmd->cmd, "unset", 6) == 0)
			cmd->builtin_type = UNSET;
		else if (ft_strncmp(cmd->cmd, "env", 4) == 0)
			cmd->builtin_type = ENV;
		else if (ft_strncmp(cmd->cmd, "pwd", 4) == 0)
			cmd->builtin_type = PWD;
		cmd = cmd->next;
	}
}

static int	count_pipe(t_token *token)
{
	int		cnt;

	cnt = 0;
	while (token != NULL)
	{
		if (token->type == PIPE)
			cnt++;
		token = token->next;
	}
	return (cnt);
}

static t_command	*prepare_cmd_lst(int num_pipe)
{
	int			i;
	t_command	*new;
	t_command	*cmd_lst;

	cmd_lst = NULL;
	i = -1;
	while (++i <= num_pipe)
	{
		new = new_cmd(NULL);
		if (new == NULL)
			exit(FAIL);
		cmd_lst_append(&cmd_lst, new);
	}
	return (cmd_lst);
}

t_command	*ft_parse(t_token *token, int *heredoc_cnt)
{
	t_command	*cmd_lst;

	if (valid_operator_syntax(token) == FALSE)
	{
		token_lst_clear(&token);
		return (NULL);
	}
	cmd_lst = prepare_cmd_lst(count_pipe(token));
	if (cmd_lst == NULL)
		exit(FAIL);
	if (init_cmd_arg(&cmd_lst, token) == FAIL)
		exit(FAIL);
	if (init_operator(&cmd_lst, token, heredoc_cnt) == FAIL)
		exit(FAIL);
	check_builtin(cmd_lst);
	token_lst_clear(&token);
	return (cmd_lst);
}
