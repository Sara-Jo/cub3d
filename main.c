/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 19:55:15 by hossong           #+#    #+#             */
/*   Updated: 2022/12/06 22:00:04 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "main.h"
#include "mlx.h"
#include <stdio.h>

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int	access_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror(file);
		return (-1);
	}
	if (ft_strncmp(ft_strchr(file, '.'), ".cub", 5) != 0)
	{
		ft_putstr_fd("no .cub\n", 2);
		return (-1);
	}
	return (fd);
}

void	file_to_data(int fd, t_data *data)
{
	char	*l;

	(void) data;
	l = get_next_line(fd);
	while (l)
	{
		if (ft_strnstr(l, "NO", 2) && ft_isspace(*(l + 2)))
			;
		else if (ft_strnstr(l, "SO", 2) && ft_isspace(*(l + 2)))
			printf("%s", l);
		else if (ft_strnstr(l, "WE", 2) && ft_isspace(*(l + 2)))
			printf("%s", l);
		else if (ft_strnstr(l, "EA", 2) && ft_isspace(*(l + 2)))
			printf("%s", l);
		else if (ft_strnstr(l, "F", 1) && ft_isspace(*(l + 1)))
			printf("%s", l);
		else if (ft_strnstr(l, "C", 1) && ft_isspace(*(l + 1)))
			printf("%s", l);
		free(l);
		l = get_next_line(fd);
	}
}

int	validate_data(t_data *data)
{
	(void) data;
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		fd;

	if (argc != 2)
		return (1);
	fd = access_file(argv[1]);
	if (fd == -1)
		return (1);
	file_to_data(fd, &data);
	if (validate_data(&data) == -1)
	{
		ft_putstr_fd("validate_data error\n", 2);
		return (1);
	}
	return (0);
}
