/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowczarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 13:15:40 by lowczarc          #+#    #+#             */
/*   Updated: 2017/11/18 19:36:14 by lowczarc         ###   ########.fr       */
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
	ret[i] = (char*)ft_memalloc((sizeof(char) * BUFF_SIZE) + sizeof(int));
	ret[i + 1] = NULL;
	*((int*)(&ret[i][BUFF_SIZE])) = fd;
	read(fd, ret[i], BUFF_SIZE);
	if (*buff != NULL)
		free(*buff);
	*buff = ret;
	return (i);
}

static int	buff_to_str(char **str, char *buff, int fd)
{
	int		i;
	int		j;
	char	*ret;

	i = ft_strlen(*str);
	j = 0;
	while (j < BUFF_SIZE && buff[j] && buff[j] != '\n')
		j++;
	if (!(ret = ft_strnew(i + j)))
		return (-2);
	ft_strcpy(ret, *str);
	ft_strncat(ret, buff, j);
	if (*str)
		free(*str);
	*str = ret;
	if (j == BUFF_SIZE)
		return (0);
	if (!buff[j])
		return (-1);
	if (buff[j] == '\n')
	{
		ft_memmove(buff, &buff[j + 1], BUFF_SIZE - j - 1);
		ft_bzero(&buff[BUFF_SIZE - j], j);
		return (1);
	}
}

int			get_next_line(const int fd, char **line)
{
	static char	**buff = NULL;
	int			buffid;
	int			t;

	buffid = realloc_buff(&buff, fd);
	*line = strdup("");
	while (1)
	{
		t = buff_to_str(line, buff[buffid], fd);
		if (t == 0)
		{
			if (read(fd, buff[buffid], BUFF_SIZE) == -1)
				return (-1);
		}
		if (t == -1)
			return (0);
		if (t == 1)
			return (1);
	}
}

int	main(int argc, char **argv)
{
	char	*str;
	int		fd;

	fd = open("test", O_RDONLY);
	while (get_next_line(fd, &str))
	{
		ft_putstr(str);
		ft_putchar('\n');
	}
	close(fd);
}
