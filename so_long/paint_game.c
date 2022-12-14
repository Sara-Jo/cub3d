/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjo <sjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 00:40:15 by sjo               #+#    #+#             */
/*   Updated: 2022/12/07 20:45:01 by sjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

void	paint_img(t_param *param, char *path, int row, int col)
{
	void	*image;
	int		width;
	int		height;

	image = mlx_xpm_file_to_image(param->mlx, path, &width, &height);
	if (!image)
		error_handler("image gen failed!");
	mlx_put_image_to_window(param->mlx, param->win, image,
		col * IMG_SIZE, row * IMG_SIZE);
	mlx_destroy_image(param->mlx, image);
}

void	paint_element(t_param *param, char tile, int row, int col)
{
	paint_img(param, "./assets/land.xpm", row, col);
	if (tile == TILE_COLLECTION)
		paint_img(param, "./assets/collection.xpm", row, col);
	else if (tile == TILE_EXIT)
	{
		if (param->game->is_possible_exit)
			paint_img(param, "./assets/exit_open.xpm", row, col);
		else
			paint_img(param, "./assets/exit_close.xpm", row, col);
	}
	else if (tile == TILE_PLAYER)
		paint_img(param, "./assets/player.xpm", row, col);
	else if (tile == TILE_WALL)
		paint_img(param, "./assets/wall.xpm", row, col);
}

void	paint_elements(t_param *param, int row_data, int row)
{
	int		col;
	char	*line;
	int	player_col = param->game->player_pos.col;
	int start_col;
	int tmp = floor(WINDOW_WIDTH / 2);

	col = 0;
	line = param->game->map[row_data];

	if (player_col < tmp) 
		start_col = 0;
	else if (player_col + tmp >= param->game->map_width)
		start_col = param->game->map_width - WINDOW_WIDTH;
	else 
		start_col = player_col - tmp; 
		
	for (int i = 0; i < WINDOW_WIDTH; i++) {
		paint_element(param, line[i + start_col], row, i);
	}
}

void	call_paint_elements(t_param *param)
{
	int player_row = param->game->player_pos.row;
	int start_row;
	int tmp = floor(WINDOW_HEIGHT / 2);

	if (player_row < tmp) 
		start_row = 0;
	else if (player_row + tmp >= param->game->map_height)
		start_row = param->game->map_height - WINDOW_HEIGHT;
	else 
		start_row = player_row - tmp;

	for (int i = 0; i < WINDOW_HEIGHT; i++) {
		paint_elements(param, i + start_row, i);
	}
}

void	paint_game(t_param *param)
{
	int	size_x;
	int	size_y;

	size_x = WINDOW_WIDTH * IMG_SIZE;
	size_y = WINDOW_HEIGHT * IMG_SIZE;
	param->mlx = mlx_init();
	if (!param->mlx)
		error_handler("mlx init failed");
	param->win = mlx_new_window(param->mlx, size_x, size_y, "sjo");
	if (!(param->win))
		error_handler("window gen failed");
	call_paint_elements(param);
}
