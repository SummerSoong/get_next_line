/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: songmengrui <songmengrui@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 21:38:00 by songmengrui       #+#    #+#             */
/*   Updated: 2023/01/25 18:08:44 by songmengrui      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;

	line = NULL;
	if (!save)
	{
		line = read_buffer(fd, &save, line);
	}
	else
	{
		line = read_save(fd, &save, line);
	}
	return (line);
}

char	*read_save(int fd, char **save, char *line)
{
	if (check_newline(*save))
	{
		*save = seperate_by_newline(*save, &line);
	}
	else
	{
		line = read_buffer(fd, save, line);
		if (!line)
		{
			line = ft_strdup(*save);
			*save = NULL;
		}
	}
	return (line);
}

char	*read_buffer(int fd, char **save, char *line)
{
	char	*buffer;
	int		rd;

	buffer = malloc(sizeof(*buffer) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	buffer[BUFFER_SIZE] = '\0';
	while ((rd = read(fd, buffer, BUFFER_SIZE)) > 0 && !line)
	{
		if (check_newline(buffer)){
			*save = seperate_by_newline(buffer, &line);
		}
		else
			*save = ft_strdup(buffer);
	}
	// if (rd == -1 || 0)
	// {
	// 	return (NULL);
	// }
	// free(buffer);
	return (line);
}

char	*seperate_by_newline(char *source, char **before)
{
	char	*after;

	after = source;
	while (*after)
	{
		if (*after == '\n')
		{
			after += 1;
			break ;;
		}
		after++;
	}
	*before = ft_substr(source, 0, ft_strlen(source) - ft_strlen(after));
	return (after);
}

int	check_newline(char *str)
{
	while (*str)
	{
		if (*str == '\n')
			return (1);
		str++;
	}
	return (0);
}
