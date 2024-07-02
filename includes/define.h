/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:48:32 by jewlee            #+#    #+#             */
/*   Updated: 2024/06/25 23:56:57 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

typedef enum	e_token_type
{
	COMMAND,
	ARGUMENT,
	INPUT_REDIRECT,
	OUTPUT_REDIRECT,
	APPEND_O_REDIRECT,
	HEREDOC,
	PIPE,
	FILE_NAME,
	END_OF_FILE,
}	t_token_type;

#endif