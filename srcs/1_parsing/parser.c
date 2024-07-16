/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:55:49 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/16 12:08:44 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
			exit(FAIL);
		cmd_lst_add_back(&cmd_lst, new);
	}
	new = cmd_lst_new(NULL);
	if (new == NULL)
		exit(FAIL);
	cmd_lst_add_back(&cmd_lst, new);
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
	cmd_lst = prepare_cmd_lst(token, cnt_pipe(token));
	if (cmd_lst == NULL)
	{
		token_lst_clear(&token);
		return (NULL);
	}
	if (init_cmd_arg(&cmd_lst, token) == FAIL)
		return (NULL);
	if (init_operator(&cmd_lst, token, heredoc_cnt) == FAIL)
	{
		token_lst_clear(&token);
		file_lst_clear(&(cmd_lst->file_lst));
		cmd_lst_clear(&cmd_lst);
		return (NULL);
	}
	check_builtin(cmd_lst);
	token_lst_clear(&token);// cmd 생성 완료후 token 할당 해제.
	return (cmd_lst);
}
