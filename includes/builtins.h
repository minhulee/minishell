/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:33:47 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/20 19:49:40 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "./basic.h"

// ft_builtins.c
void	ft_builtins(t_command *cmd, t_info *info);

// ft_builtins_cd.c
void	builtins_cd(t_command *cmd);

// ft_builtins_env.c
void	builtins_env(t_info *info);

// ft_builtins_pwd.c
void	builtins_pwd(t_command *cmd);

// ft_builtins_echo.c
void	builtins_echo(t_command *cmd);

// ft_builtins_exit.c
void	builtins_exit(t_command *cmd, t_info *info);

// ft_builtins_unset.c
void	builtins_unset(t_command *cmd, t_info *info);
char	**unset_dup_envp(t_list *env_lst);

// ft_builtins_export.c
void	builtins_export(t_command *cmd, t_info *info);

// ft_builtins_export_utils.c
void	change_env(char *arg, t_list *env_lst, char *ptr);

#endif