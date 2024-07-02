/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 19:09:23 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/02 12:10:52 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_command	*cmd_lst_new(char *cmd)
{
	t_command	*new;

	new = ft_calloc(1, sizeof(t_command));
	if (new == NULL)
		return (NULL);
	new->cmd = cmd;
	return (new);
}

void	cmd_lst_add_back(t_command **cmd_lst, t_command *new)
{
	t_command	*curr;

	if (*cmd_lst == NULL)
	{
		*cmd_lst = new;
		return ;
	}
	curr = *cmd_lst;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = new;
	new->prev = curr;
}

t_command	*cmd_lst_last(t_command *cmd)
{
	if (cmd == NULL)
		return (NULL);
	while (cmd->next != NULL)
		cmd = cmd->next;
	return (cmd);	
}

void	cmd_lst_clear(t_command **lst)
{
	t_command	*curr;
	t_command	*tmp;

	if (lst == NULL)
		return ;
	curr = *lst;
	while (curr != NULL)
	{
		tmp = curr->next;
		free(curr);
		curr = tmp;
	}
	*lst = NULL;
}

void	cmd_lst_printf(t_command *cmd_lst)
{
	int		i;
	t_file	*tmp1;
	t_file	*tmp2;

	while (cmd_lst != NULL)
	{
		printf("cmd : %s\n", cmd_lst->cmd);
		printf("cmd_path : %s\n", cmd_lst->cmd_path);
		i = 0;
		while ((cmd_lst->args)[i] != NULL)
		{
			printf("args[%d]: %s\n", i, cmd_lst->args[i]);
			i++;
		}
		tmp1 = cmd_lst->input_file;
		while (tmp1 != NULL)
		{
			printf("input_file : %s\n", tmp1->file_name);
			tmp1 = tmp1->next;
		}
		tmp2 = cmd_lst->output_file;
		while (tmp2 != NULL)
		{
			if (tmp2->type == OUTPUT_REDIRECT)
				printf("output file : %s\n", tmp2->file_name);
			else if (tmp2->type == APPEND_O_REDIRECT)
				printf("append output file : %s\n", tmp2->file_name);
			tmp2 = tmp2->next;
		}
		printf("heredoc : %s\n", cmd_lst->heredoc);
		printf("heredoc_flag : %d\n", cmd_lst->heredoc_flag);
		printf("------------\n");
		cmd_lst = cmd_lst->next;
	}
}
