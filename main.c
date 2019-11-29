#include "get_next_line.h"
#include <fcntl.h>

int main(int ac, char *av[ac])
{
	char buf[1];
	char *line;
	int fd = open(av[1], O_RDONLY);
	//read(0, buf, 1);
	int status = 1;
 	while(status != 0)
	{
	 	status = get_next_line(fd, &line);
		if (status > 0)
		{
			printf("%s\n", line);
			free(line);
		}
	}
	printf("BOUCLE FIN\n%s\n", line);
	free(line);
	close(fd);
	return 0;
}
