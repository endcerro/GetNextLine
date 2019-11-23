#include "get_next_line.h"
#include <fcntl.h>

int main()
{
    int fd = open("./toread.txt", O_RDONLY);
	//printf("FD = %d\n",fd );
	//get_next_line(fd, 0);
	//printf("END OF THE FIRST CALL\n\n\n");
	//get_next_line(fd, 0);
	//printf("END OF THE SECOND CALL\n\n\n");
	//get_next_line(fd, 0);
	//printf("END OF THE THIRD CALL\n\n\n");
	//get_next_line(fd, 0);
	//printf("END OF THE FOURTH CALL\n\n\n");
	//get_next_line(fd, 0);
	int status = 1;
	while(status != 0)
	{
		status = get_next_line(fd, 0);
	}
	return 0;
}