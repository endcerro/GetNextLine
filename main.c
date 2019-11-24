#include "get_next_line.h"
#include <fcntl.h>

int main()
{
    int fd = open("./toread.txt", O_RDONLY);
	char **line;
	line = malloc(sizeof(char*));
	if(line == NULL)
		return (0);
	*line = NULL;
	int status = 1;
	while(status != 0)
	{
		status = get_next_line(fd, line);
		if(*line != NULL)
			printf("|%s|\n",*line);
	}
	free(*line);
	free(line);
	close(fd);
	return 0;
}