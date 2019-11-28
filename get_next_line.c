/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 16:04:05 by edal--ce          #+#    #+#             */
/*   Updated: 2019/11/23 16:04:18 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin_buff(char *cache, char *s2)
{
	char	*out;
	char	*cp;
	int		size;

	size = 1;
	size += ft_strlen(cache) + BUFFER_SIZE;
	if (!cache && !s2)
		return (NULL);
	if (!(out = malloc(sizeof(char) * size)))
		return (NULL);
	cp = out;
	size = 0;
	if (cache != NULL)
		while (cache[size])
			*(out++) = cache[size++];
	size = 0;
	while (size < BUFFER_SIZE)
		*(out++) = s2[size++];
	*out = '\0';
	if (cache != NULL)
	{
		free(cache);
		cache = NULL;
	}
	return (cp);
}

char	*buff_2_cache(char *buffer, int *read_status)
{
	//printf("Appel\n");
	static char *cache;
	char *out = NULL;
	char *tmp;
	//On colle le buffer au cache
	cache = ft_strjoin_buff(cache, buffer);
	//On cherche le \n
	int end_of_line = ft_strchr_int(cache, '\n');
	//Si pas de \n et que EOF
	if(end_of_line == -1 && *read_status == 0)
		end_of_line = ft_strchr_int(cache, '\0');
	//Si on as trouvé une fin de ligne
	printf("cahce = |%s|\n",cache );
	printf("len : %d end of line : %d \n",ft_strlen(cache), end_of_line );
	if(end_of_line != -1)
	{
		//printf("read_status %d\n",*read_status );
		//On copie dans out;
		out = ft_substr(cache, 0, end_of_line);
		//printf("End of line found, copied line = |%s|\n", out);

		//Nettoyage du cache
		//printf("old cache = |%s|\n", cache);
		//tmp = ft_substr(cache, end_of_line + 1, ft_strlen(cache) - (end_of_line + 1));
		//printf("Cache len b4 dup %d, cache content %s \n",ft_strlen(cache),cache );;
		//tmp= ft_strdup(cache + end_of_line + 1);
		if(ft_strlen(cache) == 1)
		{
			printf("1\n");
			tmp = ft_strdup(cache);
		}
		else
		{
			printf("2\n");
			tmp= ft_strdup(cache + end_of_line);
		}
		//printf("Cache len aftr dup %d, cache content %s \n",ft_strlen(tmp),tmp );;
		//printf("Tmp = %s\n",tmp );
		//printf("out = %s\n",out );
		//	printf("Copie de %d len %d\n",end_of_line + 1,  ft_strlen(cache) - (end_of_line + 1));
		//printf("new cache = |%s|\n", tmp);		
		free(cache);
		cache = tmp;
		//Nettoyage du cache
	}
	//printf("cache size b4 return %d : |%s|\n",ft_strlen(cache), cache );
	if(ft_strlen(cache) > 0)
	{
		//printf("NOT OVER WE NEED ONE NORE\n"); 
		*read_status = 1;
	}
	//else
		//printf("CACHE IS DONE FOR\n"); 
	// if(cache[0] == 0)
	//    	*read_status = 0;
 	return (out);
}

// int		get_next_line(int fd, char **line)
// {
// 	char	buffer[BUFFER_SIZE];
// 	int		read_status;

// 	if (BUFFER_SIZE == 0 || fd == -1)
// 		return (-1);
// 	initbfr(buffer);
// 	read_status = read(fd, buffer, BUFFER_SIZE);
// 	*line = buff_2_cache(buffer, &read_status);
	

// 	while(ft_strlen(*line) == 0)
// 	{
// 		read_status = read(fd, buffer, BUFFER_SIZE);
// 		*line = buff_2_cache(buffer, &read_status);
// 		//printf("Line output |%s|\n",*line );
// 	}
// 	printf("returned |%s|\n",*line );
// 	return (read_status);
// }
int		get_next_line(int fd, char **line)
{
	char	buffer[BUFFER_SIZE];
	int		read_status;
	//int 	more = 0;

	if (BUFFER_SIZE == 0 || fd == -1 || line == NULL)
		return (-1);
	if (line == NULL)
		if (!(line = malloc(sizeof(char *))))
			return (0);
	initbfr(buffer);
	read_status = read(fd, buffer, BUFFER_SIZE);
	if(read_status == -1)
		return(-1);
	*line = buff_2_cache(buffer, &read_status);
	while(*line == NULL && read_status != 0)
	{
		//printf("here\n");
		//initbfr(buffer);
		read_status = read(fd, buffer, BUFFER_SIZE);
		*line = buff_2_cache(buffer, &read_status);
		//printf("status %s\n", );
		//printf("read status %d\n", read_status);
		//printf("*line = %s\n",*line );
	}
	// if(read_status != 0){initbfr(buffer);
	// 	read_status = read(fd, buffer, BUFFER_SIZE);
	// 	*line = buff_2_cache(buffer, &read_status);}
	//printf("returned |%s|\n",*line );
	//printf("read status %d\n", read_status);
	return (read_status);
}