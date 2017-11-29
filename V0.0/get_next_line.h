/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowczarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 13:12:35 by lowczarc          #+#    #+#             */
/*   Updated: 2017/11/27 19:31:50 by lowczarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef GET_NEXT_LINE_H
#	define GET_NEXT_LINE_H
#include "libft.h"
#define BUFF_SIZE 1

typedef struct	s_filesbuff
{
	int		i;
	char	**buff;
}				t_filesbuff;

int				get_next_line(const int fd, char **line);

#	endif
