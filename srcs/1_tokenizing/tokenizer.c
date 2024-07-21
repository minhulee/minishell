/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:12:58 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/21 23:34:14 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*ft_tokenize(char *line, char **envp, int exit_status)
{
	t_token	*token_lst;
	char	*expand_line;

	if (valid_quotes(line) == FALSE)
	{
		ft_fprintf(STDERR_FILENO, "Invalid quote\n");
		return (NULL);
	}
	expand_line = substitute_env(line, envp, exit_status);
	if (expand_line == NULL)
		exit(FAIL);
	free(line);
	token_lst = ft_strtok(expand_line);
	if (token_lst == NULL)
		exit(FAIL);
	free(expand_line);
	return (token_lst);
}
