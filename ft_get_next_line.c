/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: songmengrui <songmengrui@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 13:22:24 by songmengrui       #+#    #+#             */
/*   Updated: 2023/01/22 23:08:58 by songmengrui      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

#define BUFFSIZE 100

char *get_next_line(int fd)
{
	char **line;
	char *buffer;
	static char *save;
	int rd;

	buffer = malloc(sizeof(*buffer) * BUFFSIZE + 1);
	if (!buffer)
		return(NULL);
	buffer[BUFFSIZE] = '\0';

	printf("rd: %d\n", rd);
	printf("save: %s\n", save);
	printf("buffer: %s\n", buffer);

  while ((rd = read(fd, buffer, BUFFSIZE)) && buffer)
  {
		printf("-----------------\n");
		printf("save: %s\n", save);
		printf("rd: %d\n", rd);
		printf("buffer: %s\n", buffer);
    if (save)
    {
			printf("***Save exist\n");
      if (check_newline(save))
      {
				printf("***New line in save\n");
        char *save_before_newline;
        char *save_after_newline;
        seperate_by_newline(&save, &save_before_newline, &save_after_newline);
        line = &save_before_newline;
        save = ft_strjoin(save_after_newline, buffer);
				printf("line: %s\n", *line);
				printf("save: %s\n", save);
				if (!save)
					rd = 0;
      }
      else
      {
				printf("***No New line in save\n");
				printf("save: %s\n", save);
				printf("buffer: %s\n", buffer);
        *line = ft_strjoin(save, buffer);
      }

    }
    else
    {
			printf("***No save\n");
			printf("buffer: %s\n", buffer);
      if (check_newline(buffer))
      {
				printf("***newline in buffer\n");
        char *buffer_before_newline;
        char *buffer_after_newline;
        seperate_by_newline(&buffer, &buffer_before_newline, &buffer_after_newline);
        line = &buffer_before_newline;
        save = buffer_after_newline;
				printf("line: %s\n", *line);
				printf("save: %s\n", save);
      }
      else
      {
				printf("***No newline in buffer\n");
        save = buffer;
				printf("save: %s\n", save);
				printf("buffer: %s\n", buffer);
				printf("rd: %d\n", rd);
      }
    }
  }
printf("rd: %d\n", rd);
	if (save && rd == 0)
	{
		printf("*** save && rd == 0\n");
		if (check_newline(save))
		{
			printf("***New line in save\n");
			char *save_before_newline;
			char *save_after_newline;
			seperate_by_newline(&save, &save_before_newline, &save_after_newline);
			line = &save_before_newline;
			save = ft_strjoin(save_after_newline, buffer);
			printf("line: %s\n", *line);
			printf("save: %s\n", save);
		}
		else
		{
				*line = ft_strjoin(save, buffer);
		}
	}
	return (*line);
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

void seperate_by_newline(char **source, char **before, char **after)
{
	*after = ft_strchr(*source, '\n') + 1;
	*before = ft_substr(*source, 0, *after - *source);
	// printf("before: %s\n", *before);
	// printf("after: %s\n", *after);
}


int main(int argc, char *argv[])
{
  // // check seperate_by_newline
	// char *source = "hello\nworld\n42";
	// char *before = "lalala";
	// char *after = "huhuhu";
	// printf("[before]: %s\n", before);
	// printf("[after]: %s\n", after);
	// seperate_by_newline(&source, &before, &after);
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