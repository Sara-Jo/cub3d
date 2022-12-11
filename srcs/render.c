/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 15:33:08 by hossong           #+#    #+#             */
/*   Updated: 2022/12/12 01:18:45 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "libft.h"
#include "mlx.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
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
	while (x < HEIGHT)
	{
		y = 0;
		while (y < WIDTH)
		{
			color = 0xffff00;
			my_mlx_pixel_put(&a->img, y, x, color);
			color = 0x0000ff;
			my_mlx_pixel_put(&a->img, y, HEIGHT - x - 1, color);
			y++;
		}
		x++;
	}
	cast_wall(a);
	mlx_put_image_to_window(a->sc.mlx, a->sc.mlx_win, a->img.ptr, 0, 0);
}
