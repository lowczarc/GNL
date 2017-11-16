/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowczarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 13:15:40 by lowczarc          #+#    #+#             */
/*   Updated: 2017/11/16 14:09:17 by lowczarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

static int	realloc_buff(char ***buff, int fd)
{
	char	**ret;
	int		i;

	i = 0;
	while (*buff != NULL && (*buff)[i])
	{
		if (*((int*)(&(*buff)[i][BUFF_SIZE])) == fd)
			return (i);
		i++;
	}
	ret = (char**)malloc(sizeof(char*) * (i + 2));
	i = 0;
	while (*buff != NULL && (*buff)[i])
	{
		ret[i] = (*buff)[i];
		free((*buff)[i]);
		i++;
	}
	ret[i] = (char*)malloc((sizeof(char) * BUFF_SIZE) + sizeof(int));
	ret[i + 1] = NULL;
	*((int*)(&ret[i][BUFF_SIZE])) = fd;
	if (*buff != NULL)
		free(*buff);
	*buff = ret;
	return (i);
}

int			get_next_line(const int fd, char **line)
{
	static char	**buff = NULL;
	int			buffid;

	buffid = realloc_buff(&buff, fd);
}
