/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 15:33:08 by hossong           #+#    #+#             */
/*   Updated: 2022/12/11 02:27:21 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "libft.h"
#include "mlx.h"
#include <stdio.h>
#include <math.h>

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	set_dist3(t_dist3 *dist, t_vec2 *ray_dir, t_pos map, t_player *p)
{
	dist->delta = set_dist(1e30, 1e30);
	if (ray_dir->x != 0)
		dist->delta.x = fabs(1 / ray_dir->x);
	if (ray_dir->y != 0)
		dist->delta.y = fabs(1 / ray_dir->y);
	dist->step = set_dist(1.0, 1.0);
	dist->side = set_dist((map.x + 1.0 - p->row) * dist->delta.x, \
							(map.y + 1.0 - p->col) * dist->delta.y);
	if (ray_dir->x < 0)
	{
		dist->step.x = -1;
		dist->side.x = (p->row - map.x) * dist->delta.x;
	}
	if (ray_dir->y < 0)
	{
		dist->step.y = -1;
		dist->side.y = (p->col - map.y) * dist->delta.y;
	}
}

void	calc_perpenducular(t_render *ele, t_dist3 *dist, char **world)
{
	int		hit;

	hit = 0;
	while (hit == 0)
	{
		if (dist->side.x < dist->side.y)
		{
			dist->side.x += dist->delta.x;
			ele->map.x += dist->step.x;
			ele->side = 0;
		}
		else
		{
			dist->side.y += dist->delta.y;
			ele->map.y += dist->step.y;
			ele->side = 1;
		}
		if (world[ele->map.x][ele->map.y] == '1')
			hit = 1;
	}
	ele->perp_wall_dist = dist->side.x - dist->delta.x;
	if (ele->side == 1)
		ele->perp_wall_dist = dist->side.y - dist->delta.y;
}

void	draw_line(int i, t_render *ele, t_data *a)
{
	int	line_height;
	int	color;
	int	draw_start;
	int	draw_end;

	line_height = (int)(HEIGHT / ele->perp_wall_dist);
	draw_start = -line_height / 2 + HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + HEIGHT / 2;
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;
	if (a->map[ele->map.x][ele->map.y] == '1')
		color = 0x0000ff;
	if (ele->side == 1)
		color = color / 2;
	while (draw_start < draw_end)
	{
		my_mlx_pixel_put(&a->img, i, draw_start, color);
		draw_start++;
	}
}

void	render(t_data *a)
{
	t_vec2		ray_dir;
	t_dist3		dist;
	t_render	ele;
	double		cam_x;
	int			i;

	ft_bzero(a->img.addr, WIDTH * HEIGHT * a->img.bits_per_pixel / 8);
	i = 0;
	while (i < WIDTH)
	{
		cam_x = 2 * i / (double)WIDTH - 1;
		ray_dir = v_sum(a->player.dir, v_multiple(a->player.plane, cam_x));
		ele.map = set_pos((int)a->player.row, (int)a->player.col);
		set_dist3(&dist, &ray_dir, ele.map, &a->player);
		calc_perpenducular(&ele, &dist, a->map);
		draw_line(i, &ele, a);
		i++;
	}
	mlx_put_image_to_window(a->sc.mlx, a->sc.mlx_win, a->img.ptr, 0, 0);
}
