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
	int		i;

	i = 0;
	size = 1;
	//Init a 1 pour le \0
	//Si cache existe déja
	if (cache != NULL)
		size += ft_strlen(cache);
	//On prends aussi le buffer size
	size += BUFFER_SIZE;
	//Si les deux sont KO on stoppe (Pas nécéssaire ?)
	if (!cache && !s2)
		return (NULL);

	//Malloc de la sortie;
	if (!(out = malloc(sizeof(char) * size)))
		return (NULL);
	//Copie car décalage pointeur
	cp = out;
	//Tq cache n,est pas terminé on copie son contenu
	if (cache != NULL)
		while (cache[i])
			*(out++) = cache[i++];
	size = 0;
	//On copie le contenu du buffer
	while (size < BUFFER_SIZE)
		*(out++) = s2[size++];
	*out = '\0';
	
	//On free le cache actuel
	if (cache != NULL)
	{
		free(cache);
		cache = NULL;
	}
	//On renvoie le nouveau cache
	return (cp);
}

char	*buff_2_cache(char *buffer, int *read_status)
{
	static char *cache;
	char		*out;
	char		*tmp;
	int			end_of_line;

	out = NULL;
	//Join du cache et du buffer
	cache = ft_strjoin_buff(cache, buffer);
	//Si cache contient juste un \0 ??
	//Pas sur de ce bloc
	if (cache[0] == 0)
	{
		free(cache);
		cache = NULL;
		return (NULL);
	}

	//On chercher l'index du \n, -1 si il n'existe pas
	end_of_line = ft_strchr_int(cache, '\n');

	//Si read as renvoyé 0 (fin du fichier) et que on n'as pas trouveé de \n
	// -----> Cela veut dire que le cache contient la derniere ligne et donc le EOF
	if (*read_status == 0 && end_of_line == -1)
		end_of_line = ft_strchr_int(cache, '\0');
		//On cherche le EOF -> il y est forcement a la fin
	//Si on n'as ni trouveé de \n ni de \0 (last impossibru)
	//printf("Cache |%s| ",cache );
	//printf("Eol ; %d\n",end_of_line);
	if (end_of_line != -1)
	{
		//On récupére du début au \n ou \0
		out = ft_substr(cache, 0, end_of_line);
		//On actualise le cache en supprimant le début (out)
		//Utiliser strlen ? 
		tmp = ft_strdup(cache + end_of_line + 1);
		//Free du cache avant son remplacement
		if (cache != NULL)
		{
			free(cache);
			cache = NULL;
		}
		//Mise a jour du cache
		cache = tmp;
		//On as lu ? (Pas sur de cette ligne)
		*read_status = 1;
	}
	//On renvoie la ligne lue
	return (out);
}

int		get_next_line(int fd, char **line)
{
	//Init le buffer et le read status
	char	buffer[BUFFER_SIZE];
	int		read_status;

	//Remplissage du buffer de \0
	// if(buffer == NULL)
	// {
	// 	if(!(buffer = malloc(sizeof(char) * BUFFER_SIZE)))
	// 		return (0);
	// }
	initbfr(buffer);
	//Read 
	read_status = read(fd, buffer, BUFFER_SIZE);
	//Free *line si déja alloué
	if (*line != NULL)
	{
		free(*line);
		*line = NULL;
	}
	//Corps de fonction
	*line = buff_2_cache(buffer, &read_status);
	//On envoie le statut de la lecture
	return (read_status);
}

