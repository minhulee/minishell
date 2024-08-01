/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:12:58 by jewlee            #+#    #+#             */
/*   Updated: 2024/08/01 15:22:55 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	define_cmd(t_token *token)
{
	t_token	*curr;

	curr = token;
	while (curr->prev != NULL && curr->prev->type != PIPE)
		curr = curr->prev;
	while (curr && curr->type != PIPE)
	{
		if (curr->type == COMMAND)
			break ;
		if (curr->type == ARGUMENT)
		{
			curr->type = COMMAND;
			break ;
		}
		curr = curr->next;
	}
}

void	define_token_type(t_token *token)
{
	while (token)
	{
		if (token->value != NULL && token->type == ARGUMENT)
		{
			if (token->prev != NULL)
			{
				if ((token->prev->type == INPUT_REDIRECT
						|| token->prev->type == OUTPUT_REDIRECT
						|| token->prev->type == APPEND_O_REDIRECT))
					token->type = FILE_NAME;
				if (token->prev->type == HEREDOC)
					token->type = END_OF_FILE;
			}
		}
		if (token->next == NULL || token->next->type == PIPE)
			define_cmd(token);
		token = token->next;
	}
}

t_token	*ft_strtok(char *line)
{
	t_status	flag;
	t_token		*token_lst;

	flag = SUCCESS;
	token_lst = NULL;
	while (*line != '\0')
	{
		if (flag == FAIL)
			exit(FAIL);
		while (ft_isspace(*line) == TRUE)
			line++;
		if (*line == '\0')
			break ;
		if (*line == '>' || *line == '<' || *line == '|')
			flag = tokenize_operator(&line, &token_lst);
		else
			flag = tokenize_identifier(&line, &token_lst);
	}
	define_token_type(token_lst);
	return (token_lst);
}

void	init_token_info(t_token_info *info, char **envp, int exit_status)
{
	info->envp = envp;
	info->exit_status = exit_status;
}

t_token	*ft_tokenize(char *line, char **envp, int exit_status)
{
	t_token_info	info;
	t_token			*token_lst;
	char			*expand_line;

	if (valid_quotes(line) == FALSE)
	{
		ft_fprintf(STDERR_FILENO, "Invalid quote\n");
		return (NULL);
	}
	init_token_info(&info, envp, exit_status);
	expand_line = substitute_env(line, &info);
	sfree(line);
	if (expand_line == NULL)
		return (NULL);
	if (ft_strlen(expand_line) == 0)
	{
		free(expand_line);
		return (NULL);
	}
	token_lst = ft_strtok(expand_line);
	sfree(expand_line);
	if (token_lst == NULL)
		return (NULL);
	return (token_lst);
}
