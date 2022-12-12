/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 15:33:08 by hossong           #+#    #+#             */
/*   Updated: 2022/12/12 15:48:27 by hossong          ###   ########.fr       */
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

void	load_texture(t_data *a, char *path)
{
	t_img			img;
	t_wh			size;
	t_wh			idx;
	unsigned int	*dst;

	img.ptr = mlx_xpm_file_to_image(a->sc.mlx, path, &size.x, &size.y);
	dst = (unsigned int *)malloc(size.x * size.y);
	if (!img.addr || !dst)
	{
		perror(path);
		exit(1);
	}
	img.addr = mlx_get_data_addr(img.ptr, &img.bits_per_pixel, \
								&img.line_length, &img.endian);
	idx.x = 0;
	while (idx.x < size.x)
	{
		idx.y = 0;
		while (idx.y < size.y)
		{
			idx.y++;
		}
		idx.x++;
	}

	mlx_destroy_image(a->sc.mlx, img.ptr);
}

void	make_texture(unsigned int texture[8][TEXHEIGHT * TEXWIDTH])
{
	int	x;
	int	y;

	x = 0;
	while (x < TEXWIDTH)
	{
		y = 0;
		while (y < TEXHEIGHT)
		{
			int xorcolor = (x * 256 / TEXWIDTH) ^ (y * 256 / TEXHEIGHT);
			//int xcolor = x * 256 / TEXWIDTH;
			int ycolor = y * 256 / TEXHEIGHT;
			int xycolor = y * 128 / TEXHEIGHT + x * 128 / TEXWIDTH;
			texture[0][TEXWIDTH * y + x] = 65536 * 254 * (x != y && x != TEXWIDTH - y); //flat red texture with black cross
			texture[1][TEXWIDTH * y + x] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
			texture[2][TEXWIDTH * y + x] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
			texture[3][TEXWIDTH * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
			texture[4][TEXWIDTH * y + x] = 256 * xorcolor; //xor green
			texture[5][TEXWIDTH * y + x] = 65536 * 192 * (x % 16 && y % 16); //red bricks
			texture[6][TEXWIDTH * y + x] = 65536 * ycolor; //red gradient
			texture[7][TEXWIDTH * y + x] = 128 + 256 * 128 + 65536 * 128; //flat grey texture
			y++;
		}
		x++;
	}
}

void	render(t_data *a)
{
	unsigned int	texture[8][TEXHEIGHT * TEXWIDTH];
	int				x;
	int				y;
	int				color;

	make_texture(texture);
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
	load_texture(a, "./texture/wall.xpm");
	mlx_put_image_to_window(a->sc.mlx, a->sc.mlx_win, a->img.ptr, 0, 0);
}
