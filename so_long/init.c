/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjo <sjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 20:00:40 by sjo               #+#    #+#             */
/*   Updated: 2022/12/07 18:23:14 by sjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"
#include "./libft/includes/libft.h"

void	argument_checker(int argc, char *argv)
{
	char	*map_path;

	if (argc != 2)
		error_handler("Please check your arguments");
	map_path = ft_strrchr(argv, '.');
	if (!map_path || (map_path[0] != '.' || map_path[1] != 'b'
			|| map_path[2] != 'e' || map_path[3] != 'r' || map_path[4] != '\0'))
		error_handler("Please check your filename");
}

void	init(t_param *param)
{
	param->game = (t_game *)malloc(sizeof(t_game));
	if (!(param->game))
		error_handler("Game Malloc Failed");
	param->game->collection = 0;
	param->game->exit = 0;
	param->game->player = 0;
	param->game->move_count = 0;
	param->game->is_possible_exit = 0;
	param->game->is_done = 0;
	param->game->map_height = 0;
	param->game->map_width = 0;
}
