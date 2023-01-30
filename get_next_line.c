/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: songmengrui <songmengrui@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 21:38:00 by songmengrui       #+#    #+#             */
/*   Updated: 2023/01/30 11:13:21 by songmengrui      ###   ########.fr       */
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
		printf("***No save*** Call read_buffer\n");
		line = read_buffer(fd, &save, line);
		printf("**save: %s\n", save);

	}
	else
	{
		printf("***Save*** Call read_save\n");
		line = read_save(fd, &save, line);
	}
	printf("line: %s\n", line);
	return (line);
}

char	*read_save(int fd, char **save, char *line)
{
	if (check_newline(*save))
	{
		printf("nl in save\n");
		*save = seperate_by_newline(*save, &line);
		if (save == NULL)
			return (NULL);
	}
	else
	{
		printf("No nl in save\n");
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

	buffer = malloc(sizeof(*buffer) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	// buffer[BUFFER_SIZE] = '\0';
	printf("LOOP START\n");
	while (read(fd, buffer, BUFFER_SIZE) > 0 && !line)
	{
		printf("buffer: \t%s\n", buffer);
		if (check_newline(buffer))
		{
			*save = seperate_by_newline(buffer, &line);
			line = ft_strjoin(*save, line);
			printf("***nl in buffer\n");
			printf("line: \t%s\n", line);
			printf("save: \t%s\n", *save);
		}
		else
		{
			printf("***Nooo nl in buffer\n");
			printf("save before join: \t%s\n", *save);
			printf("buffer before join: \t%s\n", buffer);
			*save = ft_strjoin(*save, buffer);
			printf("save after join: \t%s\n", *save);
		}
	}
	printf("LOOP END\n");
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
			break ;
		}
		after++;
	}
	*before = ft_substr(source, 0, ft_strlen(source) - ft_strlen(after));
	if (before == NULL)
		return (NULL);
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
