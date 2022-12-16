/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjo <sjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 20:43:17 by hossong           #+#    #+#             */
/*   Updated: 2022/12/16 15:40:01 by sjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

static char	*gnl(int fd, int depth)
{
	char	*line;
	char	c;
	int		byte;

	c = 0;
	line = NULL;
	byte = read(fd, &c, 1);
	if (byte < 0 || (byte == 0 && depth == 0))
		return (NULL);
	if (c == '\n' || byte == 0)
		line = malloc(depth + 2);
	else
		line = gnl(fd, depth + 1);
	if (line)
	{
		line[depth] = c;
		line[depth + 1] = line[depth + 1] * (c != '\n');
	}
	return (line);
}

char	*get_next_line(int fd)
{
	return (gnl(fd, 0));
}

int	ft_isspace(int c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}
