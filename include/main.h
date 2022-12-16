/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjo <sjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 19:56:04 by hossong           #+#    #+#             */
/*   Updated: 2022/12/16 15:26:32 by sjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"
# include "render.h"

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
	void	*mlx;
	void	*mlx_win;
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

typedef struct s_color
{
	int r;
	int g;
	int b;
} t_color;

typedef struct s_data
{
	char *texture[4];
	int **tex_addr;
	t_color f_color;
	t_color c_color;
	char **map;
	int map_width;
	int map_height;
	t_screen sc;
	t_img img;
	t_player player;
} t_data;

int		handle_key_down(int keycode, t_data *param);
int		handle_exit(t_data *a);
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
void	render(t_data *data);
void	cast_wall(t_data *a);
void	clear_plat_data(t_data *a);
void	clear_exec_data(t_data *a);
int		validate_data(char **raw, t_data *data);
int		access_file(char *file);
void	load_texture(t_data *a);
char	**file_to_rawdata(int fd, int depth);
void	validate_map(t_data *a, char **map);
void	exit_with_error(char *str);
void	init_color(t_data *data);
int	ft_wordcount(char const *s, char *deli);
char	*ft_firstword(const char *s, char *deli);
char	**ft_inside_split(char const *s, char *deli, int nbr_of_words);
char 	**ft_split_str(char const *s, char *deli);
int	create_rgb(int r, int g, int b);

#endif
