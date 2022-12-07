/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 19:55:15 by hossong           #+#    #+#             */
/*   Updated: 2022/12/07 22:23:43 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "main.h"
#include "mlx.h"
#include <stdio.h>

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

char	**file_to_rawdata(int fd, int depth)
{
	char	**des;
	char	*line;

	des = 0;
	line = get_next_line(fd);
	if (line == NULL)
		des = (char **)malloc(sizeof(char *) * depth);
	else
		des = file_to_rawdata(fd, depth + 1);
	if (des)
		des[depth] = line;
	return (des);
}

char	**load_map(char **raw, int depth)
{
	char	**map;

	map = 0;
	if (*raw == NULL)
		map = (char **)malloc(sizeof(char *) * depth);
	else
		map = load_map(raw + 1, depth + 1);
	if (map)
		map[depth] = *raw;
	return (map);
}

int	validate_data(char **raw, t_data *data)
{
	int		i;

	i = 0;
	while (raw[i] && i < 6)
	{
		if (ft_strnstr(raw[i], "NO", 2) && ft_isspace(*(raw[i] + 2)))
			data->texture_no = raw[i];
		else if (ft_strnstr(raw[i], "SO", 2) && ft_isspace(*(raw[i] + 2)))
			data->texture_so = raw[i];
		else if (ft_strnstr(raw[i], "WE", 2) && ft_isspace(*(raw[i] + 2)))
			data->texture_we = raw[i];
		else if (ft_strnstr(raw[i], "EA", 2) && ft_isspace(*(raw[i] + 2)))
			data->texture_ea = raw[i];
		else if (ft_strnstr(raw[i], "F", 1) && ft_isspace(*(raw[i] + 1)))
			data->f_color = 1;
		else if (ft_strnstr(raw[i], "C", 1) && ft_isspace(*(raw[i] + 1)))
			data->c_color = 1;
		i++;
	}
	data->map = load_map(&raw[i], 0);
	while (*(data->map))
	{
		printf("%s", *(data->map));
		(data->map)++;
	}
	free(raw);
	return (0);
}

void	render(t_data *a)
{
	int	i;
	int	j;
	double	u;
	double	v;

	int 		x;

	double posX = 22, posY = 12;
	double dirX = 01, dirY = 0;
	double planeX = 0, planeY = 0.66;

	ft_bzero(a->img.addr, a->canv.width * a->canv.height * a->img.bits_per_pixel / 8);
	j = a->canv.height - 1;
	while (j >= 0)
	{
		i = 0;
		while (i < a->canv.width)
		{
			u = (double)i / (a->canv.width - 1);
			v = (double)j / (a->canv.height - 1);
			a->_ray = ray(a->cam.origin, \
						vminus(vplus(vplus(a->cam.left_bottom, \
						vmult(a->cam.horizontal, u)), vmult(a->cam.vertical, v)), \
						a->cam.origin));
			a->rgb = ray_color(&a->_ray, &a->sp);
			write_color(&a->img, i, a->canv.height - j - 1, a->rgb);
			i++;
		}
		j--;
	}
	mlx_put_image_to_window(a->mlx, a->mlx_win, a->img.ptr, 0, 0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		fd;
	char	**raw;

	(void) data;
	if (argc != 2)
		return (1);
	fd = access_file(argv[1]);
	if (fd == -1)
		return (1);
	raw = file_to_rawdata(fd, 0);
	if (validate_data(raw, &data) == -1)
	{
		ft_putstr_fd("validate_data error\n", 2);
		return (1);
	}
	data.sc.mlx = mlx_init();
	data.sc.mlx_win = mlx_new_window(data.sc.mlx, screenWidth, screenHeight, "hi");
	data.img.addr = mlx_get_data_addr(data.img.ptr, &data.img.bits_per_pixel, \
								&data.img.line_length, &data.img.endian);

	render(&data);
	mlx_loop(data.sc.mlx);
	return (0);
}
