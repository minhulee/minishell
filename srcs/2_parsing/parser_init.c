/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 00:15:16 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/16 12:09:20 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_status	init_arg(t_command **cmd_lst, t_token *token, int cnt)
{
	int	i;

	if (cnt == 0)
	{
		(*cmd_lst)->args = NULL;
		return (SUCCESS);
	}
	(*cmd_lst)->args = (char **)ft_calloc(cnt + 1, sizeof(char *));
	if ((*cmd_lst)->args == NULL)
		exit(FAIL);
	i = 0;
	while (i < cnt && token != NULL)
	{
		if (token->type == COMMAND || token->type == ARGUMENT)
		{
			(*cmd_lst)->args[i] = ft_strdup(token->value);
			if ((*cmd_lst)->args[i] == NULL)
				exit(FAIL);
			i++;
		}
		token = token->next;
	}
	(*cmd_lst)->args[i] = NULL;
	return (SUCCESS);
}

t_status	init_cmd_arg(t_command **cmd_lst, t_token *token)
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
			tmp->cmd = ft_strdup(token->value);
			if (tmp->cmd == NULL)
				exit(FAIL);
			cnt++;
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

t_status	init_redirect(t_command **tmp, t_token *token)
{
	t_file	*new;

	new = file_lst_new(token->type, ft_strdup(token->next->value));
	if (new == NULL)
		exit(FAIL);
	if (token->type == INPUT_REDIRECT || token->type == HEREDOC
		|| token->type == APPEND_O_REDIRECT
		|| token->type == OUTPUT_REDIRECT)
		file_lst_add_back(&((*tmp)->file_lst), new);
	return (SUCCESS);
}

t_status	init_operator(t_command **cmd_lst, t_token *token, int *heredoc_cnt)
{
	t_command	*tmp;

	tmp = *cmd_lst;
	while (token != NULL)
	{
		if (token->type == PIPE)
			tmp = tmp->next;
		else if (token->type == INPUT_REDIRECT
			|| token->type == HEREDOC
			|| token->type == OUTPUT_REDIRECT
			|| token->type == APPEND_O_REDIRECT)
		{
			if (init_redirect(&tmp, token) == FAIL)
				return (FAIL);
		}
		if (token->type == HEREDOC)
		{
			(tmp->heredoc_cnt)++;
			(*heredoc_cnt)++;
		}
		token = token->next;
	}
	return (SUCCESS);
}
