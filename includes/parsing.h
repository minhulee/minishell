/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:55:05 by jewlee            #+#    #+#             */
/*   Updated: 2024/08/01 19:48:57 by minhulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "./basic.h"
# include "./tokenizing.h"

typedef struct s_file
{
	t_token_type	type;
	char			*delimit;
	char			*file_name;
	struct s_file	*next;
}	t_file;

typedef enum e_built_type
{
	NOTBUILTIN = 0,
	CD,
	PWD,
	ENV,
	ECHO_,
	EXIT,
	UNSET,
	EXPORT,
}	t_built_type;

typedef struct s_command
{
	char				*cmd_path;
	char				*cmd;
	char				**args;
	t_built_type		builtin_type;
	int					heredoc_cnt;
	t_file				*file_lst;
	int					saved_stdout;
	int					saved_stdin;
	int					prev_pipe_fd[2];
	int					curr_pipe_fd[2];
	int					infile_fd;
	int					outfile_fd;
	t_bool				is_parent;
	struct s_command	*prev;
	struct s_command	*next;
}	t_command;

/* cmd */
t_command	*new_cmd(char *cmd);
void		cmd_lst_append(t_command **cmd_lst, t_command *src);
t_command	*cmd_lst_last(t_command *cmd);
void		cmd_lst_clear(t_command **lst);
void		cmd_lst_printf(t_command *cmd_lst);

/* file */
t_file		*new_file(t_token_type type, char *content);
void		file_lst_append(t_file **f_lst, t_file *src);
void		file_lst_clear(t_file **f_lst);

/* parser */
t_command	*ft_parse(t_token *token, int *heredoc_cnt);

/* init/init */
t_status	init_arg(t_command **cmd_lst, t_token *token, int cnt);
t_status	init_cmd_arg(t_command **cmd_lst, t_token *token);
t_status	init_operator(t_command **cmd_lst,
				t_token *token, int *heredoc_cnt);

/* init/utils */
void		increment_count_if_needed(int *cnt, t_token *token);
void		parsing_to_pipe_or_end(t_command **tmp, t_token **curr, int *cnt);

/* valid */
t_bool		valid_operator_syntax(t_token *token);

#endif