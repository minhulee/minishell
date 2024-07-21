/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:04:44 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/22 00:01:43 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTING_H
# define EXECUTING_H

# include "./basic.h"

# define TEMPFILE "/tmp/heredoc_"
# define NONE -1

// executor.c
t_status	ft_execute(t_info *info);

// executor_run.c
void 		run_commands(t_info *info, t_command *cmd, int *cnt);

// executor_path.c
char		*find_path(char **envp);
void		get_path(char **path, t_command **cmd);

// executor_heredoc.c
void		init_heredoc(t_info *info, t_command *cmd);
void		delete_heredoc(t_command *cmd);
int			process_heredoc(t_info *info, t_command *cmd);

// executor_set_fd.c
void		set_fd(t_command *cmd, t_info *info);
void		set_file_fd(t_command *cmd);
void		restore_std_fd(t_command *cmd);

// executor_set_redirect.c
void		set_redirect_fd(t_command *cmd);

// executor_clear.c
void		clear_executor(t_info *info);

// executor_valid.c
void		check_cmd_path(char *cmd_path);

#endif