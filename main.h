/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 19:56:04 by hossong           #+#    #+#             */
/*   Updated: 2022/12/11 01:29:44 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

# define WIDTH 640
# define HEIGHT 480

typedef enum e_list_of_key_code
{
	KEY_W = 13,
	KEY_S = 1,
	KEY_A = 0,
	KEY_D = 2,
	KEY_ESC = 53,
	X_EVENT_KEY_PRESS = 2,
	X_EVENT_KEY_EXIT = 17
}	t_key_code;

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

typedef struct s_player
{
	char	player_dir;
	double	row;
	double	col;
	t_vec2	dir;
	t_vec2	plane;
}	t_player;

typedef struct s_dist3
{
	t_dist	side;
	t_dist	delta;
	t_dist	step;
}	t_dist3;

typedef struct s_render
{
	t_pos	map;
	double	perp_wall_dist;
	int		side;
}	t_render;

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_screen
{
	void		*mlx;
	void		*mlx_win;
}	t_screen;

typedef struct s_data
{
	char		*texture_ea;
	char		*texture_we;
	char		*texture_so;
	char		*texture_no;
	int			f_color;
	int			c_color;
	char		**map;
	int			map_width;
	int			map_height;
	char		**view;
	t_screen	sc;
	t_img		img;
	t_player	player;
}	t_data;

char	*get_next_line(int fd);
int		ft_isspace(int c);
void	render(t_data *data);
int		access_file(char *file);
char	**file_to_rawdata(int fd, int depth);
int		validate_data(char **raw, t_data *data);
int		handle_key_down(int keycode, t_data *param);
t_vec2	vec2(double x, double y);
t_vec2	v_multiple(t_vec2 v, double k);
t_vec2	v_sum(t_vec2 v1, t_vec2 v2);
t_vec2	v_rotate(t_vec2 *vec, double rad);
void	rot_player(t_player *p, double rad);
void	set_player(t_player *p, char dir, int x, int y, double rad);
t_pos	set_pos(int x, int y);
t_dist	set_dist(double x, double y);


#endif