/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:12:33 by jewoolee          #+#    #+#             */
/*   Updated: 2024/07/18 23:45:56 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

int	fprintf_c(int fd, char c, int len)
{
	if (write(fd, &c, 1) < 0)
		return (-1);
	len++;
	return (len);
}

int	fprintf_s(int fd, char *s, int len)
{
	if (s == NULL)
	{
		len = fprintf_s(fd, "(null)", len);
		return (len);
	}
	while (*s != '\0')
	{
		len = fprintf_c(fd, *s, len);
		if (len == (-1))
			return (-1);
		s++;
	}
	return (len);
}

static int	fprintf_d_i(int fd, int num, int len)
{
	char	*s;

	s = fprintf_itoa(num);
	if (s == NULL)
		return (-1);
	len = fprintf_s(fd, s, len);
	free(s);
	s = NULL;
	return (len);
}

static int	check_specifier(int fd, va_list *ap, char c, int len)
{
	if (c == 'c')
		len = fprintf_c(fd, va_arg(*ap, int), len);
	else if (c == 's')
		len = fprintf_s(fd, va_arg(*ap, char *), len);
	else if (c == 'd' || c == 'i')
		len = fprintf_d_i(fd, va_arg(*ap, int), len);
	else if (c == 'u')
		len = fprintf_u(fd, va_arg(*ap, unsigned int), len);
	else if (c == 'x' || c == 'X')
		len = fprintf_hex(fd, va_arg(*ap, unsigned int), c, len);
	else if (c == 'p')
		len = fprintf_p(fd, va_arg(*ap, void *), len);
	else if (c == '%')
		len = fprintf_c(fd, '%', len);
	else
		len = (-1);
	return (len);
}

int	ft_fprintf(int fd, const char *format, ...)
{
	int		len;
	va_list	ap;

	if (format == NULL)
		return (-1);
	va_start(ap, format);
	len = 0;
	while (*format != '\0')
	{
		if (*format == '%')
		{
			format++;
			len = check_specifier(fd, &ap, *format, len);
		}
		else
			len = fprintf_c(fd, *format, len);
		if (len == (-1))
			break ;
		format++;
	}
	va_end(ap);
	return (len);
}
