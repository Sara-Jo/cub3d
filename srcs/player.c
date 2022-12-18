/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 18:51:42 by hossong           #+#    #+#             */
/*   Updated: 2022/12/18 14:20:02 by hossong          ###   ########.fr       */
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

t_player	set_player(char dir, int x, int y, double rad)
{
	t_player	new;

	new.dir = vec2(0.0, -1.0);
	new.plane = vec2(0.66, 0.0);
	new.player_dir = dir;
	new.col = x;
	new.row = y;
	rot_player(&new, rad);
	return (new);
}
