/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 23:57:09 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/02 13:45:30 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>

# include "./basic.h"
# include "../libft/libft.h"
# include "./define.h"
# include "./tokenizing.h"
# include "./parsing.h"
# include "./executing.h"

// typedef struct	s_info
// {
// 	int			cmd_cnt;
// 	char		*line;
// 	t_token		*token;
// 	t_command	*cmd;
// }	t_info;

#endif