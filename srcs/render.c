/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 15:33:08 by hossong           #+#    #+#             */
/*   Updated: 2022/12/09 19:35:22 by hossong          ###   ########.fr       */
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
	// double time = 0; //time of current frame
	// double oldTime = 0; //time of previous frame
	ft_bzero(a->img.addr, screenWidth * screenHeight * a->img.bits_per_pixel / 8);
	int mapX;
	int mapY;
	double sideDistX;
	double sideDistY;
	double deltaDistX;
	double deltaDistY;
	int	i = 0;
	while (i < screenWidth)
	{
		double camX = 2 * i / (double)screenWidth - 1;
		double rayDirX = a->player.dir.x + a->player.plane.x * camX;
		double rayDirY = a->player.dir.y + a->player.plane.y * camX;
		mapX = (int)a->player.row;
		mapY = (int)a->player.col;
		deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
		double perpWallDist;
		int stepX;
		int stepY;

		int hit = 0;
		int side;
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (a->player.row - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - a->player.row) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (a->player.col - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - a->player.col) * deltaDistY;
		}
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (worldMap[mapX][mapY] > 0)
				hit = 1;
		}
		if (side == 0)
			perpWallDist = (mapX - a->player.row + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - a->player.col + (1 - stepY) / 2) / rayDirY;

		int lineHeihgt = (int)(screenHeight / perpWallDist);
		int drawStart = -lineHeihgt / 2 + screenHeight / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeihgt / 2 + screenHeight / 2;
		if (drawEnd >= screenHeight)
			drawEnd = screenHeight - 1;
		int color;
		switch(worldMap[mapX][mapY])
		{
			case 1:  color = 0xff0000;  break; //red
			case 2:  color = 0x00ff00;  break; //green
			case 3:  color = 0x0000ff;   break; //blue
			case 4:  color = 0xffffff;  break; //white
			default: color = 0xffff00; break; //yellow
		}
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