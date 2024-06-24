/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 19:09:23 by jewlee            #+#    #+#             */
/*   Updated: 2024/06/23 19:02:06 by jewlee           ###   ########.fr       */
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
	while (curr)
	{
		tmp = curr->next;
		free(curr);
		curr = tmp;
	}
	*lst = NULL;
}

void	cmd_lst_printf(t_command *cmd_lst)
{
	int	i;

	while (cmd_lst != NULL)
	{
		printf("cmd : %s\n", cmd_lst->cmd);
		i = 0;
		while ((cmd_lst->args)[i] != NULL)
		{
			printf("args[%d]: %s\n", i, cmd_lst->args[i]);
			i++;
		}
		printf("infile : %s\n", cmd_lst->input_file);
		printf("outfile : %s\n", cmd_lst->output_file);
		printf("append_o_file : %s\n", cmd_lst->append_o_file);
		printf("append_o_flag : %d\n", cmd_lst->append_o_flag);
		printf("heredoc : %s\n", cmd_lst->heredoc);
		printf("heredoc_flag : %d\n", cmd_lst->heredoc_flag);
		printf("------------\n");
		cmd_lst = cmd_lst->next;
	}
}
