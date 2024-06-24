/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:55:05 by jewlee            #+#    #+#             */
/*   Updated: 2024/06/23 18:53:01 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "basic.h"
# include "define.h"

typedef struct	s_command
{
	char				*cmd;
	char				**args;
	char				*input_file; // <
	char				*heredoc; // <<
	char				*output_file; // >
	char				*append_o_file;
	t_bool				append_o_flag; // >> flag
	t_bool				heredoc_flag;
	struct s_command	*next; // pipe
}	t_command;

// parser.c
t_command	*ft_parse(t_token *token);

// parser_utils.c
int	cnt_pipe(t_token *token);

// parser_valid.c
t_bool	valid_operator_syntax(t_token *token);

// parser_valid_utils.c
t_bool	ft_isredirect(t_token_type type);

// parser_lst.c
t_command	*cmd_lst_new(char *cmd);
t_command	*cmd_lst_last(t_command *cmd);
void		cmd_lst_add_back(t_command **cmd_lst, t_command *new);
void		cmd_lst_clear(t_command **lst);
void		cmd_lst_printf(t_command *cmd_lst);


#endif