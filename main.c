#include "get_next_line.h"
#include <fcntl.h>

int main(int ac, char *av[ac])
{

    int fd = open(av[1], O_RDONLY);
	char **line;
	line = malloc(sizeof(char*));
	if(line == NULL)
		return (0);
	*line = NULL;
	int status = 1;
	//while(status != 0)
	//{
		status = get_next_line(fd, line);
		//printf("status = %d\n",status );
		//if(status > 0)
		//{
			//printf("|%s\n",*line);
			status = get_next_line(fd, line);
			printf("|%s\n",*line);
			
			//free(*line);
			//*line=NULL;
		//}
	//}
	free(*line);
	free(line);
	close(fd);
    return 0;
}