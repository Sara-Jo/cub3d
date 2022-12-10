/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:21:47 by hossong           #+#    #+#             */
/*   Updated: 2022/12/10 17:59:29 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <math.h>

static void rot_dir_plane(t_player *p, double rot_speed)
{
	p->dir = v_rotate(&p->dir, rot_speed);
	p->plane = v_rotate(&p->plane, rot_speed);
}

int	handle_key_down(int keycode, t_data *param)
{
	double moveSpeed = 0.02 * 5.0;
	double rotSpeed = M_PI / 18.0; // 180/18.0 10deg
	int	up_x;
	int	up_y;
	int down_x;
	int down_y;

	up_x = param->player.row + param->player.dir.x * moveSpeed;
	up_y = param->player.col + param->player.dir.y * moveSpeed;
	down_x = param->player.row - param->player.dir.x * moveSpeed;
	down_y = param->player.col - param->player.dir.y * moveSpeed;
	if (keycode == KEY_W)
	{
		if (param->map[up_x][(int)param->player.col] != '1')
			param->player.row += param->player.dir.x * moveSpeed;
		if (param->map[(int)param->player.row][up_y] != '1')
			param->player.col += param->player.dir.y * moveSpeed;
	}
	else if (keycode == KEY_S)
	{
		if (param->map[down_x][(int)param->player.col] != '1')
			param->player.row -= param->player.dir.x * moveSpeed;
		if (param->map[(int)param->player.row][down_y] != '1')
			param->player.col -= param->player.dir.y * moveSpeed;
	}
	else if (keycode == KEY_A)
	{
		if (param->player.player_dir == 'E' || param->player.player_dir == 'W')
			rotSpeed *= -1;
		rot_dir_plane(&param->player, rotSpeed);
	}
	else if (keycode == KEY_D)
	{
		if (param->player.player_dir == 'E' || param->player.player_dir == 'W')
			rotSpeed *= -1;
		rot_dir_plane(&param->player, -rotSpeed);
	}
	render(param);
	return (0);
}
