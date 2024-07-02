/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 02:40:32 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/02 11:29:30 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZING_H
# define TOKENIZING_H

# include "./basic.h"
# include "./define.h"

typedef struct	s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

// tokenizer.c
t_token			*ft_tokenize(char *line);

// tokenizer_append.c
t_status	append_operator(t_token_type type, char **line
	, t_token **token_lst);

// tokenizer_strtok.c
t_token	*ft_strtok(char *line);

// tokenizer_lst.c
t_token	*token_lst_new(char *value, t_token_type type);
void	token_lst_clear(t_token **lst);
void	token_lst_add_back(t_token **lst, t_token *new);

// lst_printf
void	token_lst_printf(t_token *lst);

// tokenizer_utils.c
t_bool		valid_quotes(char *line);
t_bool		ft_isspace(char c);
t_bool		ft_isquote(char c);
t_bool		ft_isoperator(char c);
t_status	skip_quotes(char *line, int *i);

// tokenizer_classify.c
void classify_identifier(t_token *token);

#endif