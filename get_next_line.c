/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 16:04:05 by edal--ce          #+#    #+#             */
/*   Updated: 2019/11/29 19:27:24 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *str, int c)
{
	while (*str)
	{
		if (*str == c)
			return ((char *)str);
		str++;
	}
	if (*str == c)
		return ((char *)str);
	return (0);
}


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

char  	*refresh_cache(char **cache)
{
	int i;

	i = 0;
	int j;

	j = 0;
	char *out;

	while((*cache)[i] != '\n' && (*cache)[i] != '\0')
		i++;
	//printf("end char = |%d|\n",(*cache)[i] );

	out = malloc(sizeof(char) * (ft_strlen(*cache) - i));
	//Protect malloc
	if((*cache)[i] != '\n')
		i++;
	printf("Current char %d\n", (*cache)[i]);
	while((*cache)[i] != '\0')
		out[j++] = (*cache)[i++];
	out[j] = '\0';
	//printf("out = %s\n",out );
	//free(*cache);
	return (out);
}

char	*get_line_from_cache(char **cache, int read_status)
{
	int i;
	char *out;
	char *tmp;
	int j;

	out = NULL;
	j = 0;
	i = ft_strchr_int(*cache, '\n');
	if(read_status == 0 && i == -1)
	 	i = ft_strchr_int(*cache, '\0');
	if(i != -1)
	{
		out = malloc(sizeof(char) * (i + 1));
		while(j < i)
		{
			out[j] = (*cache)[j];
			j++;
		}
		out[j] = '\0';
		
		*cache = refresh_cache(cache);
		//i++;
		//tmp = ft_strdup((const char *) (*cache + i));
		//free(*cache);
		//*cache = tmp;
	}
	else
		return (NULL);
	return(out);
}

int		get_next_line(int fd, char **line)
{
	char buffer[BUFFER_SIZE];
	static char *cache;
	char	*tmp;
	int read_status;

	if (BUFFER_SIZE == 0 || fd == -1 || line == NULL)
		return (-1);
	read_status = 1;
	*line = NULL;
	while(*line == NULL && read_status > 0)
	{
		initbfr(buffer);
		read_status = read(fd, buffer, BUFFER_SIZE);
		tmp = ft_strjoin_buff(cache, buffer);
		cache = tmp;
		*line = get_line_from_cache(&cache, read_status);
	}	
	if(ft_strlen(cache) > 0)
	{
		//printf("Sortie avec cache > 0\n");
		return 1;
	}
	else
	{
		//printf("Sortie avec cache =< 0\n");
		return read_status;
	}
}
