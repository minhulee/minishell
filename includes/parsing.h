/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:55:05 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/12 14:06:36 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "./basic.h"

// in | out >>, > <, <<
typedef struct s_file
{
	t_token_type	type;
	char			*delimit;
	char			*file_name;
	struct s_file	*next;
}	t_file;

typedef enum	e_built_type
{
	NOTBUILTIN = 0,
	CD,
	PWD,
	ENV,
	ECHO,
	EXIT,
	UNSET,
	EXPORT,
}	t_built_type;

typedef struct	s_command
{
	char				*cmd_path;
	char				*cmd;
	char				**args;
	t_built_type		builtin_type;
	int					heredoc_cnt;
	t_file				*file_lst;
	int					prev_pipe_fd[2];
	int					curr_pipe_fd[2];
	int					infile_fd;
	int					outfile_fd;
	t_bool				is_parent;
	struct s_command	*prev;
	struct s_command	*next; // pipe
}	t_command;

// parser.c
t_command	*ft_parse(t_token *token, int *heredoc_cnt);

// parser_utils.c
int			cnt_pipe(t_token *token);

// parser_valid.c
t_bool		valid_operator_syntax(t_token *token);

// parser_valid_utils.c
t_bool		ft_isredirect(t_token_type type);

// parser_check.c
void		check_builtin(t_command *cmd);

// parser_init.c
t_status	init_arg(t_command **cmd_lst, t_token *token, int cnt);
t_status	init_cmd_arg(t_command **cmd_lst, t_token *token);
t_status	init_operator(t_command **cmd_lst, t_token *token, int *heredoc_cnt);

// parser_lst.c
t_command	*cmd_lst_new(char *cmd);
t_command	*cmd_lst_last(t_command *cmd);
void		cmd_lst_add_back(t_command **cmd_lst, t_command *new);
void		cmd_lst_clear(t_command **lst);
void		cmd_lst_printf(t_command *cmd_lst);

// parser_f_lst.c
t_file		*file_lst_new(t_token_type type, char *content);
void		file_lst_add_back(t_file **f_lst, t_file *new);
void		file_lst_clear(t_file **lst);


#endif