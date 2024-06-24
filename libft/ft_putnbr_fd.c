/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 19:40:06 by jewlee            #+#    #+#             */
/*   Updated: 2023/10/09 19:45:38 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putnbr_fd(int n, int fd)
{
	char	last;

	if (n < 0)
	{
		if (n == -2147483648)
		{
			ft_putstr_fd("-2147483648", fd);
			return ;
		}
		ft_putchar_fd('-', fd);
		n *= (-1);
	}
	last = n % 10 + '0';
	if ((n / 10) != 0)
		ft_putnbr_fd(n / 10, fd);
	ft_putchar_fd(last, fd);
}
/*
int	main(void)
{
	ft_putnbr_fd(0, 1);
	ft_putnbr_fd(1234, 1);
	ft_putnbr_fd(-1234, 1);
	ft_putnbr_fd(-2147483648, 1);
}
*/