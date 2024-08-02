/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 19:09:23 by jewlee            #+#    #+#             */
/*   Updated: 2024/08/02 09:49:08 by minhulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_command	*new_cmd(char *cmd)
{
	t_command	*new;

	new = ft_calloc(1, sizeof(t_command));
	if (new == NULL)
		return (NULL);
	new->cmd = cmd;
	new->prev_pipe_fd[0] = NONE;
	new->prev_pipe_fd[1] = NONE;
	new->curr_pipe_fd[0] = NONE;
	new->curr_pipe_fd[1] = NONE;
	new->infile_fd = NONE;
	new->outfile_fd = NONE;
	return (new);
}

void	cmd_lst_append(t_command **cmd_lst, t_command *new)
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
	t_command	*next;
	int			i;

	if (lst == NULL)
		return ;
	curr = *lst;
	while (curr != NULL)
	{
		next = curr->next;
		file_lst_clear(&(curr->file_lst));
		sfree(curr->cmd);
		sfree(curr->cmd_path);
		if (curr->args != NULL)
		{
			i = -1;
			while (curr->args[++i] != NULL)
				free(curr->args[i]);
			free(curr->args);
		}
		free(curr);
		curr = next;
	}
	*lst = NULL;
}
