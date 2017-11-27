/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowczarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 13:15:40 by lowczarc          #+#    #+#             */
/*   Updated: 2017/11/27 19:35:12 by lowczarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	**realloc_buff(t_filesbuff *buff, int fd)
{
	char			**ret;
	int				j;

	j = 0;
	while (buff->buff != NULL && j < buff->i)
		j++;
	buff->i = ((j - 1 > fd) ? j : fd + 1);
	if (j - 1 < fd)
	{
		ret = (char**)ft_memalloc(sizeof(char*) * (buff->i + 2));
		while (--j > 0)
			ret[j] = (buff->buff)[j];
		ret[buff->i + 1] = NULL;
	}
	else
		ret = buff->buff;
	if (!ret[fd])
	{
		ret[fd] = (char*)ft_memalloc(sizeof(char) * BUFF_SIZE);
		if (read(fd, ret[fd], BUFF_SIZE) == -1)
			ret[fd] = NULL;
	}
	return (ret);
}

t_filesbuff	*newt_filesbuff(t_filesbuff *ret, int fd)
{
	if (!ret)
	{
		ret = malloc(sizeof(t_filesbuff));
		ret->i = 0;
		ret->buff = NULL;
	}
	if (fd >= 0)
		ret->buff = realloc_buff(ret, fd);
	return (ret);
}

static int	buff_to_str(char **str, char *buff, int fd)
{
	int		j;
	char	*ret;

	j = 0;
	while (j < BUFF_SIZE && buff[j] && buff[j] != '\n')
		j++;
	if (!(ret = ft_strnew(ft_strlen(*str) + j)))
		return (-2);
	ft_strcpy(ret, *str);
	ft_strncat(ret, buff, j);
	ft_memdel((void**)str);
	*str = ret;
	if (j == BUFF_SIZE)
		return (0);
	if (buff[j] == '\n' || (!buff[j] && buff[0]))
	{
		ft_memmove(buff, &buff[j + 1], BUFF_SIZE - j - 1);
		ft_bzero(&buff[BUFF_SIZE - j - 1], j + 1);
		read(fd, &buff[BUFF_SIZE - j - 1], j + 1);
		return (1);
	}
	return (-1);
}

int			get_next_line(const int fd, char **line)
{
	static t_filesbuff	*buff = NULL;
	int					t;

	buff = newt_filesbuff(buff, fd);
	if (!buff->buff[fd])
		return (-1);
	*line = ft_strdup("");
	while (1)
	{
		t = buff_to_str(line, buff->buff[fd], fd);
		if (t == 0)
		{
			bzero(buff->buff[fd], BUFF_SIZE);
			if (read(fd, buff->buff[fd], BUFF_SIZE) == -1)
				return (-1);
		}
		if (t == -1)
			return (0);
		if (t == 1)
			return (1);
		if (t == -2)
			return (-1);
	}
}
