/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 17:37:27 by hossong           #+#    #+#             */
/*   Updated: 2022/12/10 17:51:23 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <math.h>

t_vec2	vec2(double x, double y)
{
	t_vec2	new;

	new.x = x;
	new.y = y;
	return (new);
}

t_vec2	v_sum(t_vec2 v1, t_vec2 v2)
{
	t_vec2	new;
	
	new.x = v1.x + v2.x;
	new.y = v1.y + v2.y;
	return (new);
}

t_vec2	v_multiple(t_vec2 v, double k)
{
	t_vec2	new;

	new.x = v.x * k;
	new.y = v.y * k;
	return (new);
}

t_vec2	v_rotate(t_vec2 *vec, double rad)
{
	t_vec2	new;
	
	new.x = vec->x * cos(rad) - vec->y * sin(rad);
	new.y = vec->x * sin(rad) + vec->y * cos(rad);
	return (new);
}
