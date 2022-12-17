/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 22:27:24 by hossong           #+#    #+#             */
/*   Updated: 2022/12/17 13:56:20 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "main.h"
#include <math.h>
#include <limits.h>

static void	set_dist3(t_dist3 *dist, t_vec2 *ray_dir, t_pos map, t_player *p)
{
	dist->delta = set_dist(fabs(1 / ray_dir->x), fabs(1 / ray_dir->y));
	if (ray_dir->x == 0)
		dist->delta.x = 1e30;
	if (ray_dir->y == 0)
		dist->delta.y = 1e30;
	dist->step = set_dist(1.0, 1.0);
	dist->side = set_dist((map.x + 1.0 - p->col) * dist->delta.x, \
							(map.y + 1.0 - p->row) * dist->delta.y);
	if (ray_dir->x < 0)
	{
		dist->step.x = -1;
		dist->side.x = (p->col - map.x) * dist->delta.x;
	}
	if (ray_dir->y < 0)
	{
		dist->step.y = -1;
		dist->side.y = (p->row - map.y) * dist->delta.y;
	}
}

static void	calc_perpendicular(t_cast *ele, t_dist3 *dist, char **world)
{
	int		hit;

	hit = 0;
	while (hit == 0)
	{
		if (dist->side.x < dist->side.y)
		{
			dist->side.x += dist->delta.x;
			ele->map.x += dist->step.x;
			ele->side = 1;
		}
		else
		{
			dist->side.y += dist->delta.y;
			ele->map.y += dist->step.y;
			ele->side = 0;
		}
		if (world[ele->map.y][ele->map.x] == '1')
			hit = 1;
	}
	ele->perp_wall_dist = dist->side.y - dist->delta.y;
	if (ele->side == 1)
		ele->perp_wall_dist = dist->side.x - dist->delta.x;
}

static t_draw	set_draw_src(t_cast *ele, t_player *player)
{
	t_draw	src;

	if (ele->perp_wall_dist < 0.19999)
		ele->perp_wall_dist = 0.09999999999;
	src.line_height = (int)(HEIGHT / ele->perp_wall_dist);
	src.draw_start = -src.line_height / 2 + HEIGHT / 2;
	if (src.draw_start < 0)
		src.draw_start = 0;
	src.draw_end = src.line_height / 2 + HEIGHT / 2;
	if (src.draw_end <= 0 || src.draw_end >= HEIGHT)
		src.draw_end = HEIGHT - 1;
	src.wall_x = player->col + ele->perp_wall_dist * ele->ray_dir.x;
	if (ele->side == 1)
		src.wall_x = player->row + ele->perp_wall_dist * ele->ray_dir.y;
	src.wall_x -= floor(src.wall_x);
	src.tex_x = (int)(src.wall_x * (double)TEXWIDTH);
	if (ele->side == 1 && ele->ray_dir.x > 0)
		src.tex_x = TEXWIDTH - src.tex_x - 1;
	if (ele->side == 0 && ele->ray_dir.y < 0)
		src.tex_x = TEXWIDTH - src.tex_x - 1;
	src.step = 1.0 * TEXHEIGHT / src.line_height;
	src.tex_pos = (src.draw_start - HEIGHT / 2 + src.line_height / 2) \
					* src.step;
	return (src);
}

static void	draw_texture(int i, t_cast *ele, t_data *a)
{
	t_draw			src;
	int				tex_y;
	unsigned int	color;

	src = set_draw_src(ele, &a->player);
	while (src.draw_start <= src.draw_end)
	{
		tex_y = (int)src.tex_pos & (TEXHEIGHT - 1);
		src.tex_pos += src.step;
		if (ele->side == 1)
		{
			color = a->tex_addr[0][TEXHEIGHT * tex_y + src.tex_x];
			if (ele->ray_dir.x < 0)
				color = a->tex_addr[1][TEXHEIGHT * tex_y + src.tex_x];
		}
		else if (ele->side == 0)
		{
			color = a->tex_addr[2][TEXHEIGHT * tex_y + src.tex_x];
			if (ele->ray_dir.y < 0)
				color = a->tex_addr[3][TEXHEIGHT * tex_y + src.tex_x];
		}
		my_mlx_pixel_put(&a->img, i, src.draw_start, color);
		src.draw_start++;
	}
}

void	cast_wall(t_data *a)
{
	t_dist3		dist;
	t_cast		ele;
	double		cam_x;
	int			i;

	i = 0;
	while (i < WIDTH)
	{
		cam_x = 2 * i / (double)WIDTH - 1;
		ele.ray_dir = v_sum(a->player.dir, v_multiple(a->player.plane, cam_x));
		ele.map = set_pos((int)a->player.col, (int)a->player.row);
		set_dist3(&dist, &ele.ray_dir, ele.map, &a->player);
		calc_perpendicular(&ele, &dist, a->map);
		draw_texture(i, &ele, a);
		i++;
	}
}
