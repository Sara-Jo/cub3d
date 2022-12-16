/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 23:33:50 by hossong           #+#    #+#             */
/*   Updated: 2022/12/16 20:19:55 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# define WIDTH 640
# define HEIGHT 480
# define TEXHEIGHT 64
# define TEXWIDTH 64

struct s_d_xy
{
	double	x;
	double	y;
};

struct s_i_xy
{
	int	x;
	int	y;
};

typedef struct s_d_xy	t_dist;
typedef struct s_d_xy	t_vec2;
typedef struct s_i_xy	t_pos;

typedef struct s_dist3
{
	t_dist	side;
	t_dist	delta;
	t_dist	step;
}	t_dist3;

typedef struct s_cast
{
	t_pos	map;
	t_vec2	ray_dir;
	t_dist3	dist;
	double	perp_wall_dist;
	int		side;
}	t_cast;

typedef struct s_draw
{
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wall_x;
	int		tex_x;
	double	step;
	double	tex_pos;
}	t_draw;

typedef struct s_player
{
	char	player_dir;
	double	row;
	double	col;
	t_vec2	dir;
	t_vec2	plane;
}	t_player;

t_vec2		vec2(double x, double y);
t_vec2		v_multiple(t_vec2 v, double k);
t_vec2		v_sum(t_vec2 v1, t_vec2 v2);
t_vec2		v_diff(t_vec2 v1, t_vec2 v2);
t_vec2		v_rotate(t_vec2 *vec, double rad);
void		rot_player(t_player *p, double rad);
t_player	set_player(char dir, int x, int y, double rad);
t_pos		set_pos(int x, int y);
t_dist		set_dist(double x, double y);

#endif