/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 21:22:38 by jewoolee          #+#    #+#             */
/*   Updated: 2024/07/18 23:27:46 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

static void	ft_putnbr_base(int fd, unsigned long long n, char *base, int *ptr)
{
	unsigned long long		radix;

	if ((*ptr) == (-1))
		return ;
	radix = 0;
	while (base[radix] != '\0')
		radix ++;
	if (n < radix)
	{
		*ptr = fprintf_c(fd, base[n], *ptr);
		if (*ptr == (-1))
			return ;
	}
	else
	{
		ft_putnbr_base(fd, n / radix, base, ptr);
		*ptr = fprintf_c(fd, base[n % radix], *ptr);
		if (*ptr == (-1))
			return ;
	}
}

int	fprintf_p(int fd, void *ptr, int len)
{
	unsigned long long	ulld_n;
	long long			lld_n;

	if (ptr < 0)
	{
		len = fprintf_c(fd, '-', len);
		if (len == (-1))
			return (-1);
		lld_n = (long long)ptr;
		ulld_n = (unsigned long long)lld_n * (-1);
	}
	else
		ulld_n = (unsigned long long)ptr;
	len = fprintf_s(fd, "0x", len);
	if (len == (-1))
		return (-1);
	ft_putnbr_base(fd, ulld_n, "0123456789abcdef", &len);
	return (len);
}

static int	int_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static char	*put_int(char *ptr, long long num)
{
	int			i;
	long long	div;

	i = 0;
	if (num < 0)
	{
		ptr[i++] = '-';
		num *= (-1);
	}
	div = 1;
	while (num / div)
		div *= 10;
	div /= 10;
	while (1)
	{
		ptr[i++] = (num / div) + '0';
		num %= div;
		div /= 10;
		if (div == 0)
			break ;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*fprintf_itoa(int n)
{
	char			*n_str;
	int				i;
	long long		num;

	n_str = (char *)malloc(sizeof(char) * (int_len(n) + 1));
	if (n_str == 0)
		return (0);
	i = 0;
	num = (long long)n;
	if (num == 0)
	{
		n_str[i] = '0';
		n_str[i + 1] = '\0';
		return (n_str);
	}
	n_str = put_int(n_str, num);
	return (n_str);
}
