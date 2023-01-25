#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "get_next_line.h"
#define BUFFSIZE 1

int main(int argc, char *argv[])
{
    char *file_name;
    if (argc == 1)
    {
        file_name = "test.txt";
    }
    else
        file_name = argv[1];
    int fd = open(file_name, O_RDONLY);
    // int fd = 999999;
    char *line;
    int status;

    printf("\n[START] %s\n\tfd: %d\n\n", file_name, fd);
    for(int i = 0; i <= 10; i++)
		{
        line = get_next_line(fd);
				printf("============\n");
        printf("read txt:\t%s\n", line);
        free(line);
    };
    printf("\n[FINISH] %s\n", file_name);

    close(fd);
}