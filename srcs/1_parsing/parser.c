/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:55:49 by jewlee            #+#    #+#             */
/*   Updated: 2024/06/23 19:01:01 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// cmd [args...] | cmd [args...] -> 파이프 개수 + 1
static t_command	*prepare_cmd_lst(t_token *token, int num_pipe)
{
	int			i;
	t_command	*new;
	t_command	*cmd_lst;

	cmd_lst = NULL;
	i = -1;
	while (++i < num_pipe)
	{
		new = cmd_lst_new(NULL);
		if (new == NULL)
		{
			cmd_lst_clear(&cmd_lst);
			return (NULL);
		}
		cmd_lst_add_back(&cmd_lst, new);
	}
	new = cmd_lst_new(NULL);
	if (new == NULL)
	{
		cmd_lst_clear(&cmd_lst);
		return (NULL);
	}
	cmd_lst_add_back(&cmd_lst, new);
	return (cmd_lst);
}

static t_status	init_arg(t_command **cmd_lst, t_token *token, int cnt)
{
	int	i;

	(*cmd_lst)->args = (char **)ft_calloc(cnt + 2, sizeof(char *));
	if ((*cmd_lst)->args == NULL)
		return (FAIL);
	i = 0;
	while (i < cnt + 1 && token != NULL)
	{
		if (token->type == COMMAND || token->type == ARGUMENT)
		{
			(*cmd_lst)->args[i] = token->value;
			i++;
		}
		token = token->next;
	}
	(*cmd_lst)->args[i] = NULL;
	return (SUCCESS);
}

static t_status	init_cmd_arg(t_command **cmd_lst, t_token *token)
{
	t_command	*tmp;
	t_token		*curr;
	int			cnt;

	cnt = 0;
	tmp = *cmd_lst;
	while (token != NULL)
	{
		if (token->type == COMMAND)
		{
			curr = token;
			tmp->cmd = token->value;
		}
		if (token->type == ARGUMENT)
			cnt++;
		if (token->type == PIPE || token->next == NULL)
		{
			if (init_arg(&tmp, curr, cnt) == FAIL)
				return (FAIL);
			tmp = tmp->next;
			cnt = 0;
		}
		token = token->next;
	}
	return (SUCCESS);
}

void	init_operator(t_command **cmd_lst, t_token *token)
{
	t_command	*tmp;

	tmp = *cmd_lst;
	while (token != NULL)
	{
		if (token->type == PIPE)
			tmp = tmp->next;
		else if (token->type == INPUT_REDIRECT)
			tmp->input_file = token->next->value;
		else if (token->type == OUTPUT_REDIRECT)
			tmp->output_file = token->next->value;
		else if (token->type == APPEND_O_REDIRECT)
		{
			tmp->append_o_file = token->next->value;
			tmp->append_o_flag = TRUE;
		}
		else if (token->type == HEREDOC)
		{
			tmp->heredoc = token->next->value;
			tmp->heredoc_flag = TRUE;
		}
		token = token->next;
	}
}

t_command	*ft_parse(t_token *token)
{
	t_command	*cmd_lst;

	if (valid_operator_syntax(token) == FALSE)
	{
		token_lst_clear(&token);
		return (NULL);
	}
	cmd_lst = prepare_cmd_lst(token, cnt_pipe(token));
	if (cmd_lst == NULL)
	{
		token_lst_clear(&token);
		return (NULL);
	}
	init_cmd_arg(&cmd_lst, token);
	init_operator(&cmd_lst, token);
	return (cmd_lst);
}
