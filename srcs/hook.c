/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:21:47 by hossong           #+#    #+#             */
/*   Updated: 2022/12/13 12:23:42 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <math.h>

int	handle_key_down(int keycode, t_data *a)
{
	double moveSpeed = 0.02 * 5.0;
	double rad = M_PI / (18.0); // pi/18.0 1deg
	t_pos	up;
	t_pos	down;
	
	up = set_pos(a->player.row + a->player.dir.x * moveSpeed, \
					a->player.col + a->player.dir.y * moveSpeed);
	down = set_pos(a->player.row - a->player.dir.x * moveSpeed, \
					a->player.col - a->player.dir.y * moveSpeed);
	if (keycode == KEY_W)
	{
		if (a->map[up.x][(int)a->player.col] != '1')
			a->player.row += a->player.dir.x * moveSpeed;
		if (a->map[(int)a->player.row][up.y] != '1')
			a->player.col += a->player.dir.y * moveSpeed;
	}
	else if (keycode == KEY_S)
	{
		if (a->map[down.x][(int)a->player.col] != '1')
			a->player.row -= a->player.dir.x * moveSpeed;
		if (a->map[(int)a->player.row][down.y] != '1')
			a->player.col -= a->player.dir.y * moveSpeed;
	}
	else if (keycode == KEY_A)
	{
		if (a->map[(int)a->player.row][up.y] != '1')
			a->player.col += a->player.dir.y * moveSpeed;
		if (a->map[up.x][(int)a->player.col] != '1')
			a->player.row += a->player.dir.x * moveSpeed;
	}
	else if (keycode == KEY_D)
	{
		if (a->map[(int)a->player.row][down.y] != '1')
			a->player.col -= a->player.dir.y * moveSpeed;
		if (a->map[down.x][(int)a->player.col] != '1')
			a->player.row -= a->player.dir.x * moveSpeed;
	}
	else if (keycode == KEY_AR_L)
		rot_player(&a->player, rad);
	else if (keycode == KEY_AR_R)
		rot_player(&a->player, -rad);
	render(a);
	return (0);
}
