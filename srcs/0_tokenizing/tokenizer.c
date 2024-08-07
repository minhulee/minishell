/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:12:58 by jewlee            #+#    #+#             */
/*   Updated: 2024/06/26 22:51:26 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// a<b b| 연산자가 붙어있을때
// infile outfile 리스트로!~

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
