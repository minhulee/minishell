/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:23:51 by jewoolee          #+#    #+#             */
/*   Updated: 2024/07/23 14:29:40 by jewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FPRINTF_H
# define FT_FPRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

int		ft_fprintf(int fd, const char *format, ...);
int		fprintf_c(int fd, char c, int len);
int		fprintf_s(int fd, char *s, int len);
int		fprintf_u(int fd, unsigned int num, int len);
int		fprintf_hex(int fd, unsigned int num, char c, int len);
int		fprintf_p(int fd, void *ptr, int len);

char	*fprintf_itoa(int n);

#endif