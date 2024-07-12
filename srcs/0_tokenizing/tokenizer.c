/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:12:58 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/12 13:13:06 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// a<b b| 연산자가 붙어있을때
// 무조건 연산자를 기준으로 자르기~
// a"abc" -> aabc || a | abc
// export a="abc"d -> a= | abc | d

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
