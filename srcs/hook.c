/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:21:47 by hossong           #+#    #+#             */
/*   Updated: 2022/12/08 17:21:59 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	handle_key_down(int keycode, t_data *param)
{
	if (keycode == KEY_W)
	{
		param->map[param->player.row][param->player.col] = '0';
		param->player.row--;
		param->map[param->player.row][param->player.col] = 'N';
	}
	else if (keycode == KEY_A)
	{
		param->map[param->player.row][param->player.col] = '0';
		param->player.col--;
		param->map[param->player.row][param->player.col] = 'N';
	}
	else if (keycode == KEY_S)
	{
		param->map[param->player.row][param->player.col] = '0';
		param->player.row++;
		param->map[param->player.row][param->player.col] = 'N';
	}
	else if (keycode == KEY_D)
	{
		param->map[param->player.row][param->player.col] = '0';
		param->player.col++;
		param->map[param->player.row][param->player.col] = 'N';
	}
	render(param);
	return (0);
}
