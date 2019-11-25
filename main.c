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
		//if(*line != NULL)
		//	printf("|%s|\n",*line);
	}
	free(*line);
	//printf("FREED *LINE in main \n");
	free(line);
	//printf("FREED LINE  in main \n");
	close(fd);
	// while(1 == 1)
	// {

	// }
	return 0;
}