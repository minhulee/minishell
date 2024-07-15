/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewoolee <jewoolee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 19:29:11 by jewoolee          #+#    #+#             */
/*   Updated: 2023/11/18 00:10:32 by jewoolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*free_error(char **ptr, char *s)
{
	if (*ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}
	if (s != NULL)
		free(s);
	return (NULL);
}

static char	*eof_line(char **ptr, char *s)
{
	char	*line;

	free(s);
	s = NULL;
	if (*ptr == NULL)
		return (NULL);
	line = gnl_strdup(*ptr);
	free(*ptr);
	*ptr = NULL;
	if (line == NULL)
		return (NULL);
	return (line);
}

static char	*backup_line(char **ptr, size_t from)
{
	size_t	i;
	size_t	size;
	char	*backup;

	size = gnl_strlen(*ptr) - from;
	if (size < 1)
	{
		free(*ptr);
		return (NULL);
	}
	backup = (char *)malloc(sizeof(char) * (size + 1));
	if (backup == NULL || size < 1)
	{
		free(*ptr);
		return (NULL);
	}
	i = 0;
	while (i < size)
	{
		backup[i] = (*ptr)[from + i];
		i++;
	}
	backup[i] = '\0';
	free(*ptr);
	return (backup);
}

static char	*get_a_line(char **ptr)
{
	size_t	size;
	char	*line;

	size = 0;
	while ((*ptr)[size] != '\n')
		size++;
	line = (char *)malloc(sizeof(char) * (size + 2));
	if (line == NULL)
	{
		free(*ptr);
		*ptr = NULL;
		return (NULL);
	}
	line = gnl_strncpy(line, *ptr, size + 1);
	line[size + 1] = '\0';
	*ptr = backup_line(ptr, size + 1);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*rd_line;
	char		*buff;
	ssize_t		rd_size;

	if (fd < 0 || fd == 2 || BUFFER_SIZE < 1)
		return (NULL);
	while (gnl_strnl(rd_line) == 0)
	{
		buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buff == NULL)
			return (free_error(&rd_line, buff));
		rd_size = read(fd, (void *)buff, BUFFER_SIZE);
		if (rd_size < 0)
			return (free_error(&rd_line, buff));
		if (rd_size == 0)
			return (eof_line(&rd_line, buff));
		buff[rd_size] = '\0';
		rd_line = gnl_strjoin(rd_line, buff);
		if (rd_line == NULL)
			return (free_error(&rd_line, buff));
		free(buff);
	}
	return (get_a_line(&rd_line));
}
