/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:21:47 by hossong           #+#    #+#             */
/*   Updated: 2022/12/09 19:41:56 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <math.h>

t_vec2 calc(t_vec2 old)
{
	t_vec2 new;

	return (new);
}

int	handle_key_down(int keycode, t_data *param)
{
	if (keycode == KEY_W)
		param->player.row--;
	else if (keycode == KEY_A)
		param->player.col--;
	else if (keycode == KEY_S)
		param->player.row++;
	else if (keycode == KEY_D)
		param->player.col++;
	render(param);
	return (0);
}
