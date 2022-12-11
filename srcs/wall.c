/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 22:27:24 by hossong           #+#    #+#             */
/*   Updated: 2022/12/12 01:56:33 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "main.h"
#include <math.h>

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

void	calc_perpenducular(t_wall *ele, t_dist3 *dist, char **world)
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

void	draw_line(int i, t_wall *ele, t_data *a)
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

void	cast_wall(t_data *a)
{
	t_vec2		ray_dir;
	t_dist3		dist;
	t_wall		ele;
	double		cam_x;
	int			i;
	unsigned int	texture[8][TEXHEIGHT * TEXWIDTH];

	make_texture(texture);
	i = 0;
	while (i < WIDTH)
	{
		cam_x = 2 * i / (double)WIDTH - 1;
		ray_dir = v_sum(a->player.dir, v_multiple(a->player.plane, cam_x));
		ele.map = set_pos((int)a->player.row, (int)a->player.col);
		set_dist3(&dist, &ray_dir, ele.map, &a->player);
		calc_perpenducular(&ele, &dist, a->map);
		//draw_line(i, &ele, a);
		int	line_height;
		int	color;
		int	draw_start;
		int	draw_end;
		line_height = (int)(HEIGHT / ele.perp_wall_dist);
		draw_start = -line_height / 2 + HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + HEIGHT / 2;
		if (draw_end >= HEIGHT)
			draw_end = HEIGHT - 1;
		double	wall_x;
		if (ele.side == 0) wall_x = a->player.col + ele.perp_wall_dist * ray_dir.y;
		else wall_x = a->player.row + ele.perp_wall_dist * ray_dir.x;
		wall_x -= floor(wall_x);
		int tex_x = (int)(wall_x * (double)TEXWIDTH);
		if (ele.side == 0 && ray_dir.x > 0) tex_x = TEXWIDTH - tex_x - 1;
		if (ele.side == 1 && ray_dir.y < 0) tex_x = TEXWIDTH - tex_x - 1;
		double step = 1.0 * TEXHEIGHT / line_height;
		double tex_pos = (draw_start - HEIGHT / 2 + line_height / 2) * step;
		while (draw_start < draw_end)
		{
			int tex_y = (int)tex_pos & (TEXHEIGHT - 1);
			tex_pos += step;
			if (ele.side == 1)
			{
				color = texture[2][TEXHEIGHT * tex_y + tex_x];
				if (ray_dir.y < 0)
					color = texture[5][TEXHEIGHT * tex_y + tex_x];
			}
			else
			{
				color = texture[7][TEXHEIGHT * tex_y + tex_x];
				if (ray_dir.x < 0)
					color = texture[0][TEXHEIGHT * tex_y + tex_x];
			}
			my_mlx_pixel_put(&a->img, i, draw_start, color);
			draw_start++;
		}
		i++;
	}
}
