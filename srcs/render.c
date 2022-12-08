/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 15:33:08 by hossong           #+#    #+#             */
/*   Updated: 2022/12/08 21:49:40 by hossong          ###   ########.fr       */
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
	(void)a;
	// double posX = 22, posY = 12;
	double dirX = -1, dirY = 0;
	double planeX = 0, planeY = 0.66;
	int	i;
	i = 0;
	while (i < screenWidth)
	{
		double camX = 2 * i / (double)screenWidth - 1;
		double rayDirX = dirX + planeX * camX;
		double rayDirY = dirY + planeY * camX;
		
		i++;
	}
	// mlx_put_image_to_window(a->sc.mlx, a->sc.mlx_win, a->img.ptr, 0, 0);
}