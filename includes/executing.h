/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:04:44 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/18 02:52:49 by jewlee           ###   ########.fr       */
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
char		*get_cmd_path(char **path, char *cmd);
void		get_path(char **path, t_command **cmd);

// executor_heredoc.c
void		delete_heredoc(t_command *cmd);
void		process_heredoc(t_info *info, t_command *cmd);

// executor_set_fd.c
void		set_fd(t_command *cmd, t_info *info);
void		set_file_fd(t_command *cmd);

// executor_set_redirect.c
void		set_redirect_fd(t_command *cmd);

// executor_utils.c
void		err_printf(char *s);

#endif