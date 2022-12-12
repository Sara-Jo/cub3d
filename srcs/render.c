/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 15:33:08 by hossong           #+#    #+#             */
/*   Updated: 2022/12/12 22:12:46 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "libft.h"
#include "mlx.h"
#include <stdio.h>

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}


void load_image(t_data *a, unsigned int *texture, char *path)
{
	t_img	img;

	img.ptr = mlx_xpm_file_to_image(a->sc.mlx, path, &img.img_width, &img.img_height);
	if (!img.ptr)
	{
		perror(path);
		exit(1);
	}
	img.addr = mlx_get_data_addr(img.ptr, &img.bits_per_pixel, &img.line_length, &img.endian);
	for (int y = 0; y < img.img_height; y++)
	{
		for (int x = 0; x < img.img_width; x++)
			texture[img.img_width * y + x] = img.addr[img.img_width * y + x];
	}
	// mlx_destroy_image(a->sc.mlx, img.ptr);
}

unsigned int	**make_texture(t_data *a)
{
	unsigned int **des;
	int			i;

	des = (unsigned int **)malloc(sizeof(unsigned int *) * 4);
	if (!des)
		exit(1);
	i = 0;
	while (i < 4)
	{
		des[i] = (unsigned int *)malloc(sizeof(unsigned int) * (TEXHEIGHT * TEXWIDTH));
		if (!des[i])
			exit(1);
		ft_bzero(des[i], TEXHEIGHT * TEXWIDTH);
		i++;
	}
	load_image(a, des[0], a->texture[0]);
	load_image(a, des[1], a->texture[1]);
	load_image(a, des[2], a->texture[2]);
	load_image(a, des[3], a->texture[3]);
	return (des);
}

void	render(t_data *a)
{
	int				x;
	// int				y;
	// int				color;
	unsigned int		**texture;

	texture = make_texture(a);
	ft_bzero(a->img.addr, WIDTH * HEIGHT * a->img.bits_per_pixel / 8);
	x = 0;
	// while (x < HEIGHT / 2)
	// {
	// 	y = 0;
	// 	while (y < WIDTH)
	// 	{
	// 		color = 0xffff00;
	// 		my_mlx_pixel_put(&a->img, y, HEIGHT / 2 + x, color);
	// 		color = 0xff00ff;
	// 		my_mlx_pixel_put(&a->img, y, HEIGHT / 2 - x - 1, color);
	// 		y++;
	// 	}
	// 	x++;
	// }
	// cast_wall(a);
	// load_texture(a, "./texture/wall.xpm");
	mlx_put_image_to_window(a->sc.mlx, a->sc.mlx_win, a->img.ptr, 0, 0);
}
