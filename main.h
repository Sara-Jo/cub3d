/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 19:56:04 by hossong           #+#    #+#             */
/*   Updated: 2022/12/08 20:03:27 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

#define screenWidth 1024
#define screenHeight 1024

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

typedef struct s_position
{
	int	row;
	int	col;
}	t_position;

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
	char		player_dir;
	char		**view;
	t_screen	sc;
	t_img		img;
	t_position	player;
}	t_data;

char	*get_next_line(int fd);
int		ft_isspace(int c);
void	render(t_data *data);
int		access_file(char *file);
char	**file_to_rawdata(int fd, int depth);
int		validate_data(char **raw, t_data *data);
int		handle_key_down(int keycode, t_data *param);

#endif