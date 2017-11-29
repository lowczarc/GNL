/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowczarc <lowczarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 16:03:54 by lowczarc          #+#    #+#             */
/*   Updated: 2017/11/29 19:11:13 by lowczarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char		**realloc_buff(t_filesbuff *buff, int fd)
{
	char			**ret;
	int				*t;
	int				j;

	j = 0;
	while (buff->buff != NULL && j < buff->i)
		j++;
	buff->i = ((j - 1 > fd) ? j : fd + 1);
	if (j - 1 < fd)
	{
		t = (int*)ft_memalloc(sizeof(int) * buff->i + 1);
		ret = (char**)ft_memalloc(sizeof(char*) * (buff->i + 2));
		while (--j > 0)
		{
			t[j] = buff->t[j];
			ret[j] = (buff->buff)[j];
		}
		buff->t = t;
		ret[buff->i + 1] = NULL;
	}
	else
		ret = buff->buff;
	if (!ret[fd])
		ret[fd] = (char*)ft_memalloc(sizeof(char) * BUFF_SIZE);
	return (ret);
}

static char		*ft_strnjoin(char *s1, char *s2, int *n1, int n2)
{
	char	*ret;

	ret = ft_strnew(*n1 + n2);
	ft_memcpy(ret, s1, *n1);
	ft_memcpy(&ret[*n1], s2, n2);
	free(s1);
	*n1 += n2;
	return (ret);
}

static int		read_in_buff(int fd, char **line, t_filesbuff *buff, int *size)
{
	int		i;

	if (!(buff->t[fd]))
		if ((buff->t[fd] = read(fd, buff->buff[fd], BUFF_SIZE)) == 0)
			return (-1);
	i = 0;
	while (i < buff->t[fd] && buff->buff[fd][i] != '\n')
		i++;
	*line = ft_strnjoin(*line, buff->buff[fd], size, i);
	if (i < BUFF_SIZE)
	{
		ft_memmove(buff->buff[fd], &buff->buff[fd][i + 1], BUFF_SIZE - i - 1);
		ft_bzero(&(buff->buff[fd][BUFF_SIZE - i - 1]), i + 1);
	}
	if (i == buff->t[fd])
	{
		buff->t[fd] = 0;
		return (1);
	}
	else
		buff->t[fd] -= i + 1;
	return (0);
}

static void		newbuff(t_filesbuff **buff)
{
	if (!*buff)
	{
		*buff = (t_filesbuff*)malloc(sizeof(t_filesbuff));
		(*buff)->buff = NULL;
		(*buff)->t = NULL;
		(*buff)->i = 0;
	}
}

int				get_next_line(int fd, char **line)
{
	static t_filesbuff	*buff = NULL;
	int					t;
	int					size;

	if (fd < 0 || !line)
		return (-1);
	size = 0;
	*line = ft_strdup("");
	newbuff(&buff);
	buff->buff = realloc_buff(buff, fd);
	if (read(fd, buff->buff[fd], 0) == -1)
		return (-1);
	while ((t = read_in_buff(fd, line, buff, &size)) == 1)
		;
	if (t == -1 && size == 0)
		return (0);
	return (1);
}
