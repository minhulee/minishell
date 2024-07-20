/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 23:57:09 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/20 19:32:19 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <termios.h>

# include "./basic.h"
# include "../libft/libft.h"
# include "./tokenizing.h"
# include "./parsing.h"

typedef struct	s_info // -> 미니쉘에 대한 정보, 쉘 속의 쉘
{
	int					total_heredoc_cnt;
	char				*line;
	char				**og_envp;
	char				**dup_envp;
	t_list				*env_lst;
	pid_t				pid;
	t_token				*token;
	t_command			*cmd;
	int					exit_status;
	struct termios		og_term;
}	t_info;

# include "./executing.h"
# include "./builtins.h"

// 0_init/init_info.c
t_status	init_info(t_info *info, char **envp);

// 0_init/init_envp.c
t_status	init_envp(t_info *info, char **envp);

// ++
char		*super_join(char *src1, char *src2);

#endif