/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjo <sjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 19:54:39 by sjo               #+#    #+#             */
/*   Updated: 2022/12/07 20:22:09 by sjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "./mlx/mlx.h"
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>

# define IMG_SIZE 64
# define WINDOW_WIDTH 5
# define WINDOW_HEIGHT 5

typedef struct s_position
{
	int	row;
	int	col;
}	t_position;
  
typedef struct s_game
{
	char		**map;
	int			map_width;
	int			map_height;
	int			collection;
	int			exit;
	int			player;
	int			move_count;
	int			is_done;
	int			is_possible_exit;
	t_position	player_pos;
	t_position	pos;
}	t_game;

typedef struct s_param
{
	void	*mlx;
	void	*win;
	t_game	*game;
}	t_param;

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

typedef enum e_list_of_tile
{
	TILE_LAND = '0',
	TILE_WALL = '1',
	TILE_COLLECTION = 'C',
	TILE_PLAYER = 'P',
	TILE_EXIT = 'E'
}	t_tile;

void	argument_checker(int argc, char *argv);
void	init(t_param *param);
int		open_map(char *path);
void	parse_map(t_game *game, char *map_path);
void	tile_handler(t_game *game, t_tile tile, int r_idx, int c_idx);
void	column_checker(t_game *game, int r_idx, int is_wall);
void	row_checker(t_game *game);
void	check_map(t_game *game);
void	move_w(t_param *param);
void	move_a(t_param *param);
void	move_s(t_param *param);
void	move_d(t_param *param);
int		handle_key_down(int keycode, t_param *param);
void	paint_img(t_param *param, char *path, int row, int col);
void	paint_element(t_param *param, char tile, int row, int col);
void	paint_elements(t_param *param, int row_data, int row);
void	call_paint_elements(t_param *param);
void	paint_game(t_param *param);
void	error_handler(char *reason);
int		handle_exit_game(t_param *param);
int		handle_force_exit_game(t_param *param);
int		handle_complete_game(t_param *param);
void	print_move_count(int count);
char	*get_next_line(int fd);

#endif
