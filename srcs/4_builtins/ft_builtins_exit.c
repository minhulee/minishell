/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 22:03:05 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/22 15:21:42 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_bool	check_num(char *s)
{
	int	n_cnt;
	int	digit_cnt;

	n_cnt = 0;
	digit_cnt = 0;
	while (*s != '\0')
	{
		if ((*s == '+' || *s == '-')
			&& *(s + 1) != '\0' && ft_isdigit(*(s + 1)) == 0)
			return (FALSE);
		if (ft_isdigit(*s) == 1 && (*(s + 1) == ' ' || *(s + 1) == '\0'))
			n_cnt++;
		if (n_cnt > 1)
			return (FALSE);
		if (ft_isdigit(*s) == 1)
			(digit_cnt)++;
		s++;
	}
	if (digit_cnt <= 0)
		return (FALSE);
	return (TRUE);
}

static t_bool	check_sign(char *s)
{
	int	sign_cnt;

	sign_cnt = 0;
	while (*s != '\0')
	{
		if (*s == '+' || *s == '-')
			sign_cnt++;
		if (sign_cnt > 1)
			return (FALSE);
		s++;
	}
	return (TRUE);
}

static t_bool	check_args(char *s)
{
	int		i;

	i = -1;
	while (s[++i] != '\0')
	{
		if (s[i] != ' ' && s[i] != '+' && s[i] != '-'
			&& ft_isdigit(s[i]) == FALSE)
			return (FALSE);
	}
	if (check_sign(s) == FALSE)
		return (FALSE);
	if (check_num(s) == FALSE)
		return (FALSE);
	return (TRUE);
}

void	exit_process(char *args)
{
	int		exit_value;

	exit_value = ft_atoi(args);
	if (exit_value < 0)
		while (exit_value < 0)
			exit_value += 256;
	if (exit_value > 255)
		exit_value = exit_value % 256;
	exit(exit_value);
}

void	builtins_exit(t_command *cmd, t_info *info)
{
	printf("exit\n");
	if (cmd->args[1] == NULL)
		exit(1);
	if (check_args(cmd->args[1]) != TRUE)
	{
		ft_fprintf(STDERR_FILENO,
			"minishell: exit: %s: numeric argument required\n", cmd->args[1]);
		exit(255);
	}
	if (cmd->args[2] != NULL)
	{
		ft_fprintf(STDERR_FILENO, "minishell: exit: too many arguments\n");
		if (cmd->is_parent != TRUE)
			exit(1);
		else
			info->exit_status = FAIL;
	}
	else
		exit_process(cmd->args[1]);
}
