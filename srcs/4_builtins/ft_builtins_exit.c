/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 22:03:05 by jewlee            #+#    #+#             */
/*   Updated: 2024/07/20 19:55:18 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_bool	check_num(char *s)
{
	int	n_flag;
	int	digit_cnt;

	n_flag = 0;
	digit_cnt = 0;
	while (*s != '\0')
	{
		if ((*s == '+' || *s == '-')// (부호)-> 부호 다음 공백
			&& *(s + 1) != '\0' && ft_isdigit(*(s + 1)) == 0)
			return (FALSE);
		if (ft_isdigit(*s) == 1 && (*(s + 1) == ' ' || *(s + 1) == '\0'))// "1 1 1"
			n_flag++;
		if (n_flag > 1)
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
	if (exit_value > 255)
		exit_value = exit_value % 256;
	exit(exit_value);
}

// cat a | echo hello | exit asf -> 마지막 프로세스 기준 종료 상태.
void	builtins_exit(t_command *cmd, t_info *info)
{
	int	size;

	printf("exit\n");
	if (cmd->args[1] == NULL)
		exit(1);
	if (check_args(cmd->args[1]) != TRUE)
	{
		ft_fprintf(STDERR_FILENO,
			"minishell: exit: %s: numeric argument required\n", cmd->args[1]);
		exit(255);
	}
	size = -1;
	while (cmd->args[++size] != NULL) ;// exit 1 2 3 -> 
	if (size - 1 > 1)
	{
		ft_fprintf(STDERR_FILENO, "minishell: exit: too many arguments\n");
		if (cmd->is_parent != TRUE)
			exit(1);
		else
			info->exit_status = 1;
	}
	else
		exit_process(cmd->args[1]);
}
