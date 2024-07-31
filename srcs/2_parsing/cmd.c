/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 19:09:23 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/31 09:46:14 by jewlee           ###   ########.fr       */
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
	t_command	*tmp;
	int			i;

	if (lst == NULL)
		return ;
	curr = *lst;
	while (curr != NULL)
	{
		tmp = curr->next;
		if (curr->cmd != NULL)
			free(curr->cmd);
		if (curr->cmd_path != NULL)
			free(curr->cmd_path);
		if (curr->args != NULL)
		{
			i = -1;
			while (curr->args[++i] != NULL)
				free(curr->args[i]);
			free(curr->args);
		}
		free(curr);
		curr = tmp;
	}
	*lst = NULL;
}

// void	cmd_lst_printf(t_command *cmd_lst)
// {
// 	int		i;
// 	t_file	*tmp;

// 	while (cmd_lst != NULL)
// 	{
// 		printf("cmd : %s\n", cmd_lst->cmd);
// 		printf("cmd_path : %s\n", cmd_lst->cmd_path);
// 		i = 0;
// 		while (cmd_lst->args != NULL && (cmd_lst->args)[i] != NULL)
// 		{
// 			printf("args[%d]: %s\n", i, cmd_lst->args[i]);
// 			i++;
// 		}
// 		tmp = cmd_lst->file_lst;
// 		while (tmp != NULL)
// 		{
// 			if (tmp->type == HEREDOC)
// 			{
// 				printf("heredoc : %s\n", tmp->delimit);
// 				if (tmp->file_name != NULL)
// 					printf("file_name : %s\n", tmp->file_name);
// 			}
// 			else
// 				printf("file_name : %s\n type : %d\n", tmp->file_name, tmp->type);
// 			tmp = tmp->next;
// 		}
// 		printf("heredoc_cnt : %d\n", cmd_lst->heredoc_cnt);
// 		printf("Builtin %d\n", cmd_lst->builtin_type);
// 		printf("------------\n");
// 		cmd_lst = cmd_lst->next;
// 	}
// }
