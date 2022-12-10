/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 18:51:42 by hossong           #+#    #+#             */
/*   Updated: 2022/12/11 01:28:45 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_pos	set_pos(int x, int y)
{
	t_pos	new;

	new.x = x;
	new.y = y;
	return (new);
}

t_dist	set_dist(double x, double y)
{
	t_dist	new;

	new.x = x;
	new.y = y;
	return (new);
}

void	rot_player(t_player *p, double rad)
{
	p->dir = v_rotate(&p->dir, rad);
	p->plane = v_rotate(&p->plane, rad);
}

void	set_player(t_player *p, char dir, int x, int y, double rad)
{
	p->player_dir = dir;
	p->row = x;
	p->col = y;
	rot_player(p, rad);
}

void	view_north(t_data *a)
{
	int player_row = a->player.row;
	int distance_from_player;
	int i = 0;

	// row: player_row 부터 0번째 row까지 탐색
	while (player_row) {
		// col: 처음부터 끝까지 탐색
		while (i < WIDTH) {
			if (a->map[player_row][i] == '1') {
				distance_from_player = a->player.row - player_row;
				//my_mlx_pixel_put(&a->img, player_row, i, 0xff0000);
				(void) distance_from_player;
			}
			else if (a->map[player_row][i] == '0')
				;
				//my_mlx_pixel_put(&a->img, player_row, i, 0x00ff00);
			// else if (a->map[y][x] == 'N')
			//	 my_mlx_pixel_put(&a->img, x, y, 0x0000ff);
			i++;
		}
		player_row--;
	}
}
