/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 19:56:04 by hossong           #+#    #+#             */
/*   Updated: 2022/12/13 17:17:06 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"
# include "render.h"

# define texWidth 64
# define texHeight 64

typedef enum e_list_of_key_code
{
	KEY_W = 13,
	KEY_S = 1,
	KEY_A = 0,
	KEY_D = 2,
	KEY_AR_L = 123,
	KEY_AR_R = 124,
	KEY_ESC = 53,
	X_EVENT_KEY_PRESS = 2,
	X_EVENT_KEY_EXIT = 17
}	t_key_code;

typedef struct s_screen
{
	void		*mlx;
	void		*mlx_win;
}	t_screen;

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		img_width;
	int		img_height;
}	t_img;

typedef struct s_data
{
	char		*texture[4];
	int			**tex_addr;
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

char		*get_next_line(int fd);
int			ft_isspace(int c);
void		my_mlx_pixel_put(t_img *data, int x, int y, int color);
void		render(t_data *data);
int			access_file(char *file);
char		**file_to_rawdata(int fd, int depth);
int			validate_data(char **raw, t_data *data);
int			handle_key_down(int keycode, t_data *param);
int			handle_exit(t_data *a);
void		cast_wall(t_data *a);
void		load_texture(t_data *a);
void		free_str(char **str);

#endif
