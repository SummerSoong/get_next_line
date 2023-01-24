/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: songmengrui <songmengrui@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 21:38:00 by songmengrui       #+#    #+#             */
/*   Updated: 2023/01/24 22:23:38 by songmengrui      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#define BUFFSIZE 100

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;

	line = NULL;
	printf("save: %s\n", save);
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
	}
	return (line);
}

char	*read_buffer(int fd, char **save, char *line)
{
	char	*buffer;

	buffer = malloc(sizeof(*buffer) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	buffer[BUFFER_SIZE] = '\0';
	while (read(fd, buffer, BUFFER_SIZE) && !line)
	{
		if (check_newline(buffer))
			*save = seperate_by_newline(buffer, &line);
		else
			*save = ft_strdup(buffer);
	}
	return (line);
}

char	*seperate_by_newline(char *source, char **before)
{
	char	*after;

	after = ft_strchr(source, '\n') + 1;
	*before = ft_substr(source, 0, after - source);
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

int main()
{
  // // check seperate_by_newline
	// char *source = "hello\nworld\n42";
	// char *before = "lalala";
	// char *after = "huhuhu";
	// printf("[before]: %s\n", before);
	// printf("[after]: %s\n", after);
	// after = seperate_by_newline(source, &before);
	// printf("[before]: %s\n", before);
	// printf("[after]: %s\n", after);
	int fd;

	fd = open("test.txt", O_RDONLY);

	for (int i = 0; i <= 3; i++)
		{
			printf("===================\n");
			printf("Get_next_line: %s\n", get_next_line(fd));
		}
}