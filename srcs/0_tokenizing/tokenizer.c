/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:12:58 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/16 00:21:15 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// line -> token 왠만하면 새로 duplicate
t_token	*ft_tokenize(char *line)
{
	t_token	*token_lst;

	if (valid_quotes(line) == FALSE)
	{
		printf("Quotes errors\n");
		return (NULL);
	}
	token_lst = ft_strtok(line);
	free(line);
	return (token_lst);
}
