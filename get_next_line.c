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
	int		size;
	int		i;

	i = -1;
	size = 1;
	size += ft_strlen(cache);
	size += BUFFER_SIZE;
	if (!cache && !s2)
		return (NULL);
	if (!(out = malloc(sizeof(char) * size)))
		return (NULL);
	if (cache != NULL)
		while (cache[++i])
			out[i] = cache[i];
	size = 0;
	while (size < BUFFER_SIZE)
		out[i++] = s2[size++];
	out[i] = '\0';
	if (cache != NULL)
	{
		free(cache);
		cache = NULL;
	}
	return (out);
}

char	*buff_2_cache(char *buffer, int *read_status)
{
	static char *cache;
	char		*out;
	char		*tmp;
	int			end_of_line;

	out = NULL;
	cache = ft_strjoin_buff(cache, buffer);
	end_of_line = ft_strchr_int(cache, '\n');
	if (*read_status == 0 && end_of_line == -1)
		end_of_line = ft_strchr_int(cache, '\0');
	if (end_of_line != -1)
	{
		out = ft_substr(cache, 0, end_of_line);
		tmp = ft_strdup(cache + end_of_line + 1);
		if (cache != NULL)
			free(cache);
		cache = tmp;
	}
	if (ft_strlen(cache) == 0 && *read_status == 0)
		*read_status = 0;
	else
		*read_status = 1;
	return (out);
}

int		get_next_line(int fd, char **line)
{
	char	buffer[BUFFER_SIZE];
	int		read_status;

	if (BUFFER_SIZE == 0 || fd == -1)
		return (-1);
	if (line == NULL)
		if (!(line = malloc(sizeof(char *))))
			return (0);
	initbfr(buffer);
	read_status = read(fd, buffer, BUFFER_SIZE);
	if (*line != NULL)
	{
		free(*line);
		*line = NULL;
	}
	*line = buff_2_cache(buffer, &read_status);
	return (read_status);
}
