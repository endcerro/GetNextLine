#include "get_next_line.h"
#include <fcntl.h>

int main(int ac, char *av[ac])
{
	char buf[1];
	char *line;
	int fd = open(av[1], O_RDONLY);
	//read(0, buf, 1);
	int status = 1;
	char *test = ft_strdup("This is the sample text first \n second line, two empty \n\n and a final one");
	printf("|%s|\n",test );
	printf("|%s|\n",refresh_cache(&test));
	printf("|%s|\n",refresh_cache(&test));
	printf("|%s|\n",refresh_cache(&test));
 // 	while(status != 0)
	// {
	//  	status = get_next_line(fd, &line);
	// 	printf("|%s\n", line);
	// 	//free(line);
	// }
	//printf("BOUCLE FIN\n%s\n", line);
	//status = get_next_line(fd, &line);
	//printf("BOUCLE FIN\n%s\n", line);
	free(line);
	close(fd);
	return 0;
}
