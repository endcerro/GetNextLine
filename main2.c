/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoreau <vmoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 17:00:43 by vmoreau           #+#    #+#             */
/*   Updated: 2019/12/05 15:24:18 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

int		main(int ac, char *av[])
{
	int		fd;
	char	*str;
	int		ret;

	str = NULL;
	ret = 1;
	fd = open(av[ac-1], O_RDONLY);
	while (ret > 0)
	{
		ret = get_next_line(fd, &str);
		if (ret != -1)
			printf("%d %s\n",ret, str);
		free(str);
	}
	ret = get_next_line(fd, &str);
//		if (ret != -1)
	printf("%d %s\n",ret, str);
	return (0);
}
