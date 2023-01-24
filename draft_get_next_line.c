/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draft_get_next_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: songmengrui <songmengrui@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 13:22:24 by songmengrui       #+#    #+#             */
/*   Updated: 2023/01/24 22:16:57 by songmengrui      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

#define BUFFSIZE 10

char *get_next_line(int fd)
{
	char *line;
	char *buffer;
	static char *save;
	int rd;

	buffer = malloc(sizeof(*buffer) * BUFFSIZE + 1);
	if (!buffer)
		return(NULL);
	buffer[BUFFSIZE] = '\0';

	printf("save: %s\n", save);
	printf("buffer: %s\n", buffer);


  while ((rd = read(fd, buffer, BUFFSIZE)) && buffer)
  {
		printf("-----------------\n");
		printf("save: %s\n", save);
		printf("rd: %d\n", rd);
		printf("buffer: %s\n", buffer);
    if (!save)
    {
			printf("***No save\n");
			printf("buffer: %s\n", buffer);
      if (check_newline(buffer))
      {
				printf("***newline in buffer\n");
        save = seperate_by_newline(buffer, &line);
				printf("rd: %d\n", rd);
				printf("line: %s\n", line);
				printf("save: %s\n", save);
				return (line);
      }
      else
      {
				printf("***No newline in buffer\n");
        save = ft_strdup(buffer);
				printf("save: %s\n", save);
				printf("buffer: %s\n", buffer);
				printf("rd: %d\n", rd);
      }

			printf("save: %s\n", save);
    }
		else
    {
			printf("***Save exist\n");
      if (check_newline(save))
      {
				printf("***New line in save\n");
        save = ft_strjoin(seperate_by_newline(save, &line), buffer);
				printf("line: %s\n", line);
				printf("save: %s\n", save);
				return (line);
      }
      else
      {
				printf("***No New line in save\n");
				printf("save: %s\n", save);
				printf("buffer: %s\n", buffer);
				save = ft_strjoin(save, buffer);
        line = save;
      }

    }

		printf("At the end of while loop, save: %s\n", save);
  }

	// Save exist, No rd
	if (save && !rd)
	{
		line = get_line_from_save(&save);
		return (line);
	}
	return (0);
}


char *get_line_from_save(char **save)
{
	char *line;

	printf("*** save && rd == 0\n");
	if (check_newline(*save))
	{
		printf("***New line in save\n");
		*save = seperate_by_newline(*save, &line);
		printf("line: %s\n", line);
		printf("save: %s\n", *save);
		printf("check_newline(save): %d\n", check_newline(*save));
	}
	else
	{
			printf("***No new line in save\n");
			printf("save: %s\n", *save);
			line = *save;
			// free(save);
	}
	printf("save: %s\n", *save);
	return (line);
}

int check_newline(char *str)
{
	while (*str)
	{
		if (*str == '\n')
			return (1);
		str++;
	}
	return (0);
}

char *seperate_by_newline(char *source, char **before)
{
	char *after;

	after = ft_strchr(source, '\n') + 1;
	*before = ft_substr(source, 0, after - source);

	return (after);
	// printf("before: %s\n", *before);
	// printf("after: %s\n", *after);
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