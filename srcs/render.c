/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 15:33:08 by hossong           #+#    #+#             */
/*   Updated: 2022/12/13 04:48:34 by hossong          ###   ########.fr       */
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


void load_image(t_data *a, int *texture, char *path)
{
	t_img	img;
	int		*data;

	img.ptr = mlx_xpm_file_to_image(a->sc.mlx, path, &img.img_width,
									&img.img_height);
	if (!img.ptr)
	{
		perror(path);
		exit(1);
	}
	data = (int *)mlx_get_data_addr(img.ptr, &img.bits_per_pixel, &img.line_length, &img.endian);
	for (int y = 0; y < img.img_height; y++)
	{
		for (int x = 0; x < img.img_width; x++)
			texture[img.img_width * y + x] = data[img.img_width * y + x];
	}
	mlx_destroy_image(a->sc.mlx, img.ptr);
}

void	make_texture(t_data *a)
{
	int			i;

	a->tex_addr = (int **)malloc(sizeof(int *) * 4);
	i = 0;
	while (i < 4)
	{
		a->tex_addr[i] = (int *)malloc(sizeof(int) * (TEXHEIGHT * TEXWIDTH));
		ft_bzero(a->tex_addr[i], TEXHEIGHT * TEXWIDTH);
		i++;
	}
	load_image(a, a->tex_addr[0], a->texture[0]);
	load_image(a, a->tex_addr[1], a->texture[1]);
	load_image(a, a->tex_addr[2], a->texture[2]);
	load_image(a, a->tex_addr[3], a->texture[3]);
}

void	render(t_data *a)
{
	int				x;
	int				y;
	int				color;

	ft_bzero(a->img.addr, WIDTH * HEIGHT * a->img.bits_per_pixel / 8);
	x = 0;
	while (x < HEIGHT / 2)
	{
		y = 0;
		while (y < WIDTH)
		{
			color = 0xffff00;
			my_mlx_pixel_put(&a->img, y, HEIGHT / 2 + x, color);
			color = 0xff00ff;
			my_mlx_pixel_put(&a->img, y, HEIGHT / 2 - x - 1, color);
			y++;
		}
		x++;
	}
	cast_wall(a);
	mlx_put_image_to_window(a->sc.mlx, a->sc.mlx_win, a->img.ptr, 0, 0);
}
