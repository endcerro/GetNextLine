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
	int		sz;
	int		i;

	i = 0;
	sz = 1;
	if (cache)
		sz += ft_strlen(cache);
	sz += BUFFER_SIZE;
	if (!cache && !s2)
		return (0);
	if (!(out = malloc(sizeof(char) * sz)))
		return (0);
	cp = out;
	if (cache != NULL)
		while (cache[i])
			*(out++) = cache[i++];
	sz = 0;
	while (sz < BUFFER_SIZE)
		*(out++) = s2[sz++];
	*out = 0;
	if (cache != NULL)
		free(cache);
	return (cp);
}

char	*buff_2_cache(char *buffer, int *read_status)
{
	static char *cache;
	char		*out;
	char		*tmp;
	int			end_of_line;

	out = NULL;
	cache = ft_strjoin_buff(cache, buffer);
	if (cache[0] == 0)
	{
		free(cache);
		cache = NULL;
		return (NULL);
	}
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
		*read_status = 1;
	}
	return (out);
}

int		get_next_line(int fd, char **line)
{
	char	buffer[BUFFER_SIZE];
	int		read_status;

	initbfr(buffer);
	read_status = read(fd, buffer, BUFFER_SIZE);
	if (*line != NULL)
		free(*line);
	*line = buff_2_cache(buffer, &read_status);
	return (read_status);
}
