/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_classify.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 15:00:37 by jewlee            #+#    #+#             */
/*   Updated: 2024/06/22 15:57:26 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// | cmd
// < > >> file_name, << eof
// cmd [args..] | cmd [args..] 
// << eof cmd, cmd << eof
void	classify_identifier(t_token *token)
{
	while (token != NULL)
	{
		if (token->value != NULL && token->type == ARGUMENT)
		{
			if (token->prev != NULL)
			{
				if ((token->prev->type == INPUT_REDIRECT
						|| token->prev->type == OUTPUT_REDIRECT
						|| token->prev->type == APPEND_O_REDIRECT))
					token->type = FILE_NAME;
				else if (token->prev->type == HEREDOC)
					token->type = END_OF_FILE;
				else if (token->prev->type == FILE_NAME
						|| token->prev->type == END_OF_FILE
						|| token->prev->type == PIPE)
					token->type = COMMAND;
			}
			else
				token->type = COMMAND;
		}
		token = token->next;
	}
}
