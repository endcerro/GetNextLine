#include "get_next_line.h"
#include <fcntl.h>

int main(int ac, char *av[ac])
{

    int fd = open(av[1], O_RDONLY);
	char **line;
	line = malloc(sizeof(char*));
	//printf("MALLOC LINE  in main \n");
	if(line == NULL)
		return (0);
	*line = NULL;
	int status = 1;
	while(status != 0)
	{
		status = get_next_line(fd, line);
		//printf("status %d\n",status );
		if(*line != NULL)
			printf("|%s\n",*line);
	}
	free(*line);
	free(line);
	close(fd);
	// while(1 == 1)
	// {
	//gcc -Wall -Wextra -Werror -g -fsanitize=address -D BUFFER_SIZE=23 get_next_line.c get_next_line_utils.c main.c
	// }
	return 0;
}
