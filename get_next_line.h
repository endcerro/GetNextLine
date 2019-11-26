/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 16:04:58 by edal--ce          #+#    #+#             */
/*   Updated: 2019/11/23 16:05:00 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>

# include <stdio.h>

# include <unistd.h>


typedef struct		fd_lst
{
	int				*fd;
	char			*cache;
	struct fd_lst	*next;
	struct fd_lst	*previous;

}					fd_list;

void	initbfr(char *buff);
int		get_next_line(int fd, char **line);
char	*ft_strjoin(char *s1, char *s2);
void	mvebfr(char *buffer, int buffsize);
int		ft_strlen(char *str);
char	*ft_strjoin_buff(char *cache, char *s2);
int		ft_strchr_int(const char *str, int c);
char	*ft_substr(char const *s, int start, size_t len);
char	*ft_strdup(const char *s1);

#endif
