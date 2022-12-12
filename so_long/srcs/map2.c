/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:02:45 by sjo               #+#    #+#             */
/*   Updated: 2022/12/08 15:00:34 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"
#include "../libft/includes/libft.h"

void	check_map(t_game *game)
{
	int	i;

	i = 0;
	game->map_width = ft_strlen(game->map[0]);
	while ((game->map[i++]) != NULL)
		;
	game->map_height = i - 1;
	row_checker(game);
	if (!(game->collection > 0 && game->exit > 0 && game->player == 1))
		error_handler("Map is invalid");
		
	for (int i = 0; i < game->map_height; i++){
		for (int j = 0; j < game->map_width; j++) {
			if (game->map[i][j] == 'P') {
				game->player_pos.row = i;
				game->player_pos.col = j;
			}
		}
	}
}
