/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:04:44 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/02 12:38:16 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTING_H
# define EXECUTING_H

# include "./basic.h"
# include "./define.h"

// executor.c
t_status	ft_execute(t_command *cmd, char **envp);

// executor_run.c
void 		run_commands(t_command *cmd);

// executor_path.c
char		*find_path(char **envp);
char		*get_cmd_path(char **path, char *cmd);
t_status	get_path(char **path, t_command **cmd);

// executor_utils.c
int	cmd_cnt(t_command *cmd);

#endif