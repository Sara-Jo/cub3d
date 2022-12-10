/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 18:51:42 by hossong           #+#    #+#             */
/*   Updated: 2022/12/10 18:55:08 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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

