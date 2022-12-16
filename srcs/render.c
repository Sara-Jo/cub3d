/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjo <sjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 15:33:08 by hossong           #+#    #+#             */
/*   Updated: 2022/12/16 15:27:15 by sjo              ###   ########.fr       */
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

static void	xpm_to_image(t_data *a, int *texture, char *path)
{
	t_img	i;
	int		*data;
	int		x;
	int		y;

	ft_bzero(&i, sizeof(t_img));
	i.ptr = mlx_xpm_file_to_image(a->sc.mlx, path, &i.img_width, &i.img_height);
	if (!i.ptr)
	{
		perror(path);
		clear_exec_data(a);
		clear_plat_data(a);
		exit(1);
	}
	data = (int *)mlx_get_data_addr(i.ptr, &i.bits_per_pixel, &i.line_length, \
																	&i.endian);
	y = -1;
	while (++y < i.img_height)
	{
		x = -1;
		while (++x < i.img_width)
			texture[i.img_width * y + x] = data[i.img_width * y + x];
	}
	mlx_destroy_image(a->sc.mlx, i.ptr);
}

void	load_texture(t_data *a)
{
	int			i;

	a->tex_addr = (int **)malloc(sizeof(int *) * 4);
	i = 0;
	while (i < 4)
		a->tex_addr[i++] = 0;
	i = 0;
	while (i < 4)
	{
		a->tex_addr[i] = (int *)malloc(sizeof(int) * (TEXHEIGHT * TEXWIDTH));
		ft_bzero(a->tex_addr[i], TEXHEIGHT * TEXWIDTH);
		xpm_to_image(a, a->tex_addr[i], a->texture[i]);
		i++;
	}
}

void	render(t_data *a)
{
	int				x;
	int				y;
	int				color;

	ft_bzero(a->img.addr, WIDTH * HEIGHT * a->img.bits_per_pixel / 8);
	y = 0;
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			color = create_rgb(a->f_color.r, a->f_color.g, a->f_color.b);
			my_mlx_pixel_put(&a->img, x, HEIGHT / 2 + y, color);
			color = create_rgb(a->c_color.r, a->c_color.g, a->c_color.b);
			my_mlx_pixel_put(&a->img, x, HEIGHT / 2 - y - 1, color);
			x++;
		}
		y++;
	}
	cast_wall(a);
	mlx_put_image_to_window(a->sc.mlx, a->sc.mlx_win, a->img.ptr, 0, 0);
}
