/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 15:33:08 by hossong           #+#    #+#             */
/*   Updated: 2022/12/10 19:34:37 by hossong          ###   ########.fr       */
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
	*(unsigned int*)dst = color;
}

void	view_north(t_data *a)
{
	int player_row = a->player.row;
	int distance_from_player;
	int i = 0;

	// row: player_row 부터 0번째 row까지 탐색
	while (player_row) {
		// col: 처음부터 끝까지 탐색
		while (i < screenWidth) {
			if (a->map[player_row][i] == '1') {
				distance_from_player = a->player.row - player_row;
				my_mlx_pixel_put(&a->img, player_row, i, 0xff0000);
				(void) distance_from_player;
			}
			else if (a->map[player_row][i] == '0')
				my_mlx_pixel_put(&a->img, player_row, i, 0x00ff00);
			// else if (a->map[y][x] == 'N')
			//	 my_mlx_pixel_put(&a->img, x, y, 0x0000ff);
			i++;
		}
		player_row--;
	}
}

void	render(t_data *a)
{
	t_pos	map;
	t_dist	side_dist;
	t_dist	delta_dist;
	t_vec2	ray_dir;
	
	ft_bzero(a->img.addr, screenWidth * screenHeight * a->img.bits_per_pixel / 8);
	int	i = 0;
	while (i < screenWidth)
	{
		double camX = 2 * i / (double)screenWidth - 1;
		ray_dir = v_sum(a->player.dir, v_multiple(a->player.plane, camX));
		map = set_pos((int)a->player.row, (int)a->player.col);
		delta_dist.x = (ray_dir.x == 0) ? 1e30 : fabs(1 / ray_dir.x);
		delta_dist.y = (ray_dir.y == 0) ? 1e30 : fabs(1 / ray_dir.y);
		double perpWallDist;
		int stepX;
		int stepY;

		int hit = 0;
		int side;
		if (ray_dir.x < 0)
		{
			stepX = -1;
			side_dist.x = (a->player.row - map.x) * delta_dist.x;
		}
		else
		{
			stepX = 1;
			side_dist.x = (map.x + 1.0 - a->player.row) * delta_dist.x;
		}
		if (ray_dir.y < 0)
		{
			stepY = -1;
			side_dist.y = (a->player.col - map.y) * delta_dist.y;
		}
		else
		{
			stepY = 1;
			side_dist.y = (map.y + 1.0 - a->player.col) * delta_dist.y;
		}
		while (hit == 0)
		{
			if (side_dist.x < side_dist.y)
			{
				side_dist.x += delta_dist.x;
				map.x += stepX;
				side = 0;
			}
			else
			{
				side_dist.y += delta_dist.y;
				map.y += stepY;
				side = 1;
			}
			if (a->map[map.x][map.y] == '1')
				hit = 1;
		}
		if (side == 0)
			perpWallDist = side_dist.x - delta_dist.x;
		else
			perpWallDist = side_dist.y - delta_dist.y;

		int lineHeihgt = (int)(screenHeight / perpWallDist);
		int drawStart = -lineHeihgt / 2 + screenHeight / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeihgt / 2 + screenHeight / 2;
		if (drawEnd >= screenHeight)
			drawEnd = screenHeight - 1;
		int color;
		if (a->map[map.x][map.y] == '1')
			color = 0x0000ff;
		if (side == 1)
			color = color / 2;
		while (drawStart < drawEnd)
		{
			my_mlx_pixel_put(&a->img, i, drawStart, color);
			drawStart++;
		}
		i++;
	}
	mlx_put_image_to_window(a->sc.mlx, a->sc.mlx_win, a->img.ptr, 0, 0);
}