/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_valid_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 17:11:47 by jewlee            #+#    #+#             */
/*   Updated: 2024/06/22 18:14:04 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	ft_isredirect(t_token_type type)
{
	if (type == INPUT_REDIRECT || type == OUTPUT_REDIRECT
		|| type == APPEND_O_REDIRECT || type == HEREDOC)
		return (TRUE);
	return (FALSE);
}
