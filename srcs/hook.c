/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:21:47 by hossong           #+#    #+#             */
/*   Updated: 2022/12/18 14:32:53 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "mlx.h"
#include <math.h>

int	handle_exit(t_data *a)
{
	clear_exec_data(a);
	clear_plat_data(a);
	exit(0);
}

static void	move_pos_negative(t_data *a, t_vec2 v, int postive)
{
	double	move_speed;
	t_pos	move_postive;
	t_pos	move_negative;

	move_speed = 0.6;
	move_postive = set_pos(a->player.col + v.x * move_speed, \
							a->player.row + v.y * move_speed);
	move_negative = set_pos(a->player.col - v.x * move_speed, \
							a->player.row - v.y * move_speed);
	if (postive)
	{
		if (a->map[move_postive.y][(int)a->player.col] != '1')
			a->player.row += v.y * move_speed;
		if (a->map[(int)a->player.row][move_postive.x] != '1')
			a->player.col += v.x * move_speed;
	}
	else
	{
		if (a->map[move_negative.y][(int)a->player.col] != '1')
			a->player.row -= v.y * move_speed;
		if (a->map[(int)a->player.row][move_negative.x] != '1')
			a->player.col -= v.x * move_speed;
	}
}

int	handle_key_down(int keycode, t_data *a)
{
	double	rad;

	rad = M_PI / (18.0);
	if (keycode == KEY_W)
		move_pos_negative(a, a->player.dir, 1);
	else if (keycode == KEY_S)
		move_pos_negative(a, a->player.dir, 0);
	else if (keycode == KEY_D)
		move_pos_negative(a, a->player.plane, 1);
	else if (keycode == KEY_A)
		move_pos_negative(a, a->player.plane, 0);
	else if (keycode == KEY_AR_L)
		rot_player(&a->player, -rad);
	else if (keycode == KEY_AR_R)
		rot_player(&a->player, rad);
	else if (keycode == KEY_ESC)
		handle_exit(a);
	render(a);
	return (0);
}
