/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:21:47 by hossong           #+#    #+#             */
/*   Updated: 2022/12/12 20:41:12 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <math.h>

int	handle_key_down(int keycode, t_data *param)
{
	double 	moveSpeed = 0.02 * 5.0;
	double 	rad = M_PI / (18.0); // pi/18.0 1deg
	t_pos	up;
	t_pos	down;
	
	up = set_pos(param->player.row + param->player.dir.x * moveSpeed, \
					param->player.col + param->player.dir.y * moveSpeed);

	up_x = ;
	up_y = ;
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
		rot_player(&param->player, rad);
	else if (keycode == KEY_D)
		rot_player(&param->player, -rad);
	render(param);
	return (0);
}
