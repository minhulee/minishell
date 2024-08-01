/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 23:57:50 by jewlee            #+#    #+#             */
/*   Updated: 2024/08/01 15:02:33 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_file	*new_file(t_token_type type, char *content)
{
	t_file	*new;

	if (content == NULL)
		return (NULL);
	new = ft_calloc(1, sizeof(t_file));
	if (new == NULL)
		exit(FAIL);
	new->type = type;
	if (type == HEREDOC)
		new->delimit = super_join(content, ft_strdup("\n"));
	else
		new->file_name = content;
	return (new);
}

void	file_lst_append(t_file **f_lst, t_file *new)
{
	t_file	*curr;

	if (*f_lst == NULL)
	{
		*f_lst = new;
		return ;
	}
	curr = *f_lst;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = new;
}

void	file_lst_clear(t_command *cmd)
{
	t_command	*cur_cmd;
	t_file		*cur_file;
	t_file		*next;

	if (cmd->file_lst == NULL)
		return ;
	cur_cmd = cmd;
	while (cur_cmd != NULL)
	{
		cur_file = cur_cmd->file_lst;
		while (cur_file != NULL)
		{
			sfree(cur_file->file_name);
			sfree(cur_file->delimit);
			next = cur_file->next;
			sfree(cur_file);
			cur_file = next;
		}
		cur_cmd = cur_cmd->next;
	}
}
