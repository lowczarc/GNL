/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowczarc <lowczarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 17:22:49 by lowczarc          #+#    #+#             */
/*   Updated: 2017/11/28 22:33:54 by lowczarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include <fcntl.h>

int main(int argc, char **argv)
{
	char	*str;
	int		fd;
	int		i;

	fd = open(argv[1], O_RDONLY);
	while (1)
	{
		i = get_next_line(fd, &str);
		ft_putstr(str);
		ft_putnbr(i);
		ft_putchar('\n');
		if (i != 1)
			break;
	}
}
